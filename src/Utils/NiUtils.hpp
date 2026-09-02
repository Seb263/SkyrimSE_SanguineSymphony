#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Utils/MiscUtils.hpp"

class NiUtils
{
public:

	static bool IsReferenceRagdollReady(RE::TESObjectREFR* ref)
	{
		if (!ref || !ref->Is3DLoaded()) return false;

		RE::NiAVObject* niAVObject = ref->Get3D();
		if (!niAVObject) return false;

		auto* hkpRigidBody = GetRigidBody(niAVObject);
		if (hkpRigidBody && hkpRigidBody->world && hkpRigidBody->motion.GetMass() > 0.0f) return true;

		return false;
	}

	static void ApplyImpulseToReference(RE::TESObjectREFR* ref, RE::NiPoint3 direction, float linearImpulseMagnitude, float angularImpulseMagnitude)
	{
		if (!ref) return;

		if (RE::NiAVObject* niAVObject = ref->Get3D()) {
			ApplyImpulseToRigidBody(niAVObject, direction, linearImpulseMagnitude, angularImpulseMagnitude);
		}
	}

	static void ApplyImpulseToRigidBody(RE::NiAVObject* niAVObject, RE::NiPoint3 direction, float linearImpulseMagnitude, float angularImpulseMagnitude, const bool ignoreMass = false)
	{
		auto hkpRigidBody = GetRigidBody(niAVObject);
		if (!hkpRigidBody) return;

		const float bodyMass = (!ignoreMass ? hkpRigidBody->motion.GetMass() : 1.0f);
		if (!std::isfinite(bodyMass) || bodyMass <= 0.0f) return;

		if (!std::isfinite(direction.x) || !std::isfinite(direction.y) || !std::isfinite(direction.z)) return;

		direction.Unitize();
		float norm = direction.Length();
		if (norm == 0.0f || !std::isfinite(norm)) return;
		direction /= norm;

		if (!std::isfinite(linearImpulseMagnitude) || !std::isfinite(angularImpulseMagnitude)) return;

		RE::hkVector4 linearImpulse = {
			direction.x * linearImpulseMagnitude,
			direction.y * linearImpulseMagnitude,
			direction.z * linearImpulseMagnitude,
			0.0f
		};
		linearImpulse = linearImpulse * bodyMass;
		ClampVector4(linearImpulse, 3000.0f);
		hkpRigidBody->motion.ApplyLinearImpulse(linearImpulse);

		RE::hkVector4 angularImpulse = {
			(MiscUtils::GetRandomNumber(-0.022f, 0.022f)) * bodyMass,
			(MiscUtils::GetRandomNumber(-0.022f, 0.022f)) * bodyMass,
			angularImpulseMagnitude * bodyMass,
			0.0f
		};
		ClampVector4(angularImpulse, 3000.0f);
		hkpRigidBody->motion.ApplyAngularImpulse(angularImpulse);
	}

	static void ClampVector4(RE::hkVector4& vec, const float maxMagnitude)
	{
		const float x = vec.quad.m128_f32[0];
		const float y = vec.quad.m128_f32[1];
		const float z = vec.quad.m128_f32[2];

		if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
			vec.quad = _mm_setzero_ps();
			return;
		}

		const float magnitudeSq = x * x + y * y + z * z;
		alignas(16) float mask[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

		if (!std::isfinite(magnitudeSq)) {
			vec.quad = _mm_setzero_ps();
			return;
		}

		if (magnitudeSq > maxMagnitude * maxMagnitude) {
			const float scale = maxMagnitude / std::sqrt(magnitudeSq);
			mask[0] = mask[1] = mask[2] = scale;
		}
		vec.quad = _mm_mul_ps(vec.quad, _mm_load_ps(mask));
	}

	static RE::hkpRigidBody* GetRigidBody(RE::NiAVObject* a_object)
	{
		if (!a_object) return nullptr;

		auto* collisionObject = a_object->GetCollisionObject();
		if (!collisionObject) return nullptr;

		auto bhkRigidBody = RE::NiPointer<RE::bhkRigidBody>(collisionObject->GetRigidBody());
		if (!bhkRigidBody || !bhkRigidBody->referencedObject) return nullptr;

		auto* hkpRigidBody = static_cast<RE::hkpRigidBody*>(bhkRigidBody->referencedObject.get());
		return hkpRigidBody;
	}

	/**
	 * ============================================================================
	 * Generic helpers for Ni*ExtraData
	 * ----------------------------------------------------------------------------
	 * Provides templates to store, retrieve, and update typed ExtraData
	 * (bool, int, float, string) on NiAVObject without code duplication.
	 * ============================================================================
	 */

	template <class T>
	struct ExtraDataTraits;

	template <>
	struct ExtraDataTraits<RE::NiBooleanExtraData>
	{
		using ValueType = bool;

		static RE::NiBooleanExtraData* Create(const std::string& name, ValueType value)
		{
			return RE::NiBooleanExtraData::Create(name, value);
		}

		static ValueType& GetValue(RE::NiBooleanExtraData* data)
		{
			return data->data;
		}
	};

	template <>
	struct ExtraDataTraits<RE::NiIntegerExtraData>
	{
		using ValueType = std::int32_t;

		static RE::NiIntegerExtraData* Create(const std::string& name, ValueType value)
		{
			return RE::NiIntegerExtraData::Create(name, value);
		}

		static ValueType& GetValue(RE::NiIntegerExtraData* data)
		{
			return data->value;
		}
	};

	template <>
	struct ExtraDataTraits<RE::NiFloatExtraData>
	{
		using ValueType = float;

		static RE::NiFloatExtraData* Create(const std::string& name, ValueType value)
		{
			return RE::NiFloatExtraData::Create(name, value);
		}

		static ValueType& GetValue(RE::NiFloatExtraData* data)
		{
			return data->value;
		}
	};

	template <>
	struct ExtraDataTraits<RE::NiStringExtraData>
	{
		using ValueType = const char*;

		static RE::NiStringExtraData* Create(const std::string& name, ValueType value)
		{
			auto* data = new RE::NiStringExtraData();
			data->name = name;
			data->value = _strdup(value);
			return data;
		}

		static char*& GetValue(RE::NiStringExtraData* data)
		{
			return data->value;
		}
	};

	template <class T>
	static void StoreExtraData(RE::NiAVObject* a_object, const std::string& name, const typename ExtraDataTraits<T>::ValueType& value, const bool overrideExisting = false)
	{
		if (!a_object) return;

		if (auto* existing = a_object->GetExtraData<T>(name)) {
			if (overrideExisting) {
				ExtraDataTraits<T>::GetValue(existing) = value;
			}
			return;
		}

		auto* newData = ExtraDataTraits<T>::Create(name, value);
		a_object->InsertExtraData(newData);
	}

	template <class T>
	static std::optional<typename ExtraDataTraits<T>::ValueType> GetExtraDataValue(RE::NiAVObject* a_object, const std::string& name)
	{
		if (!a_object) return std::nullopt;

		auto* extra = a_object->GetExtraData<T>(name);
		if (!extra) return std::nullopt;

		return ExtraDataTraits<T>::GetValue(extra);
	}

	template <class T>
	static bool UpdateExtraDataValue(RE::NiAVObject* a_object, const std::string& name, typename ExtraDataTraits<T>::ValueType& outValue)
	{
		auto newValue = GetExtraDataValue<T>(a_object, name);
		if (!newValue.has_value()) return false;

		if (outValue != *newValue) {
			outValue = *newValue;
			return true;
		}

		return false;
	}
};
