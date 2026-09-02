#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Core/Structure.h"

#include "Utils/MiscUtils.hpp"
#include "Utils/NiUtils.hpp"

namespace ModCore
{
	using namespace CoreStructure;

	class BloodPool
	{
	public:

		static void RecordLastHitNode(RE::Actor* actor, const RuntimeHitContext& context, bool& alreadyHadHitNode)
		{
			if (!actor || context.bipedEntry.bipedNode.empty()) return;
			
			std::lock_guard<std::mutex> lock(s_nodeMapMutex);

			alreadyHadHitNode = (s_lastHitNodes.find(actor->formID) != s_lastHitNodes.end());

			bool enabledForWeapon = false;
			using WeaponType = Filter::WeaponType;
			switch (context.weaponType) {
				case WeaponType::kHandToHand:
				case WeaponType::kBeast:
					enabledForWeapon = SettingsIni::bBloodpools_EnableForUnarmed;
					break;

				case WeaponType::kOneHandSword:
				case WeaponType::kTwoHandSword:
				case WeaponType::kOneHandAxe:
				case WeaponType::kTwoHandAxe:
				case WeaponType::kDagger:
					enabledForWeapon = SettingsIni::bBloodpools_EnableForBlades;
					break;

				case WeaponType::kOneHandMace:
				case WeaponType::kTwoHandMace:
					enabledForWeapon = SettingsIni::bBloodpools_EnableForBlunt;
					break;

				case WeaponType::kRanged:
					enabledForWeapon = SettingsIni::bBloodpools_EnableForRanged;
					break;

				case WeaponType::kMagic:
					enabledForWeapon = SettingsIni::bBloodpools_EnableForMagic;
					break;
				}

			if (!enabledForWeapon) return;

			
			s_lastHitNodes[actor->formID] = context.bipedEntry.bipedNode;
		}

		static void ProcessBloodpool(RE::Actor* victimRef)
		{
			using namespace ModData;

			const auto process = ([](RE::Actor* victimRef) -> bool {
				if (!victimRef || !ModData::DBF_API_Interface || !IsActorValid(victimRef)) return false;

				if (!SettingsIni::bBloodpools_Status) return false;
				if ((SettingsIni::fBloodpools_Chances / 100.0f) < MiscUtils::GetRandomNumber()) return false;

				auto* race = victimRef->GetRace();
				if (!race) return false;

				auto* material = race->bloodImpactMaterial;
				if (!material) return false;

				if (material->IsDynamicForm()) material = material->parentType;
				if (!material) return false;

				bool status = false;
				float scaleMin = 1.0f;
				float scaleMax = 1.0f;
				float durationMin = 1.0f;
				float durationMax = 1.0f;
				std::string profileID = "";

				switch (material->formID) {
				case 0x12F3F:
				case 0x5A28F:
				case 0xC1AD7:
					// Default
			
					status = SettingsIni::bBloodpools_DefaultStatus;
					scaleMin = SettingsIni::fBloodpools_Default_ScaleMin;
					scaleMax = SettingsIni::fBloodpools_Default_ScaleMax;
					durationMin = SettingsIni::fBloodpools_Default_DurationMin;
					durationMax = SettingsIni::fBloodpools_Default_DurationMax;
					profileID = "SanguineSymphony-Default";
					break;
				case 0x10D5CC:
					// Insect
					status = SettingsIni::bBloodpools_InsectStatus;
					scaleMin = SettingsIni::fBloodpools_Insect_ScaleMin;
					scaleMax = SettingsIni::fBloodpools_Insect_ScaleMax;
					durationMin = SettingsIni::fBloodpools_Insect_DurationMin;
					durationMax = SettingsIni::fBloodpools_Insect_DurationMax;
					profileID = "SanguineSymphony-Insect";
					break;
				case 0x9644C:
				case 0x9150B:
					// Dwarven
					status = SettingsIni::bBloodpools_AutomatonStatus;
					scaleMin = SettingsIni::fBloodpools_Automaton_ScaleMin;
					scaleMax = SettingsIni::fBloodpools_Automaton_ScaleMax;
					durationMin = SettingsIni::fBloodpools_Automaton_DurationMin;
					durationMax = SettingsIni::fBloodpools_Automaton_DurationMax;
					profileID = "SanguineSymphony-Dwarven";
					break;
				default:
					break;
				}

				if (!status) return false;
				if (scaleMin > scaleMax) std::swap(scaleMin, scaleMax);
				if (durationMin > durationMax) std::swap(durationMin, durationMax);

				auto* closestNode = GetCachedNodeForActor(victimRef);
				if (!closestNode) return false;

				float actorRadius = 0.0f;
				if (auto* rootNode = victimRef->Get3D()) actorRadius = rootNode->worldBound.radius;

				constexpr float maxRadiusMult = 1.15f;
				constexpr float minRadius = 32.0f;

				const float computedMaxRadius = std::min(GetMaxRadius(victimRef) * 82.0f * maxRadiusMult, 500.0f);

				const float maxRadius = std::max(computedMaxRadius, minRadius);
				const float clampedRadius = std::clamp(actorRadius, minRadius, maxRadius);

				const float scale = clampedRadius / 82.0f;

				DBF_API::Interface::Parameters p;
				p.profileID = profileID;
				p.waitForStableOrigin = true;
				p.originRef = victimRef;
				p.originNodePos = closestNode;

				p.override.scale = scale * MiscUtils::GetRandomNumber(scaleMin, scaleMax);
				p.override.durationMult = MiscUtils::GetRandomNumber(durationMin, durationMax);

				p.override.spread = 360.0f;

				p.callback = [](bool result, RE::TESObjectREFR*) {
					TRACE("Bloodpool spawning {}", result ? "completed successfully" : "failed");
				};
				ModData::DBF_API_Interface->SpawnBloodpool(p);

				return true;
			})(victimRef);

			if (!process) RemoveCachedNodeForActor(victimRef);
		}

		static void PurgeNodeMap()
		{
			std::lock_guard<std::mutex> lock(s_nodeMapMutex);
			s_lastHitNodes.clear();
		}

		static void RemoveCachedNodeForActor(RE::Actor* actor)
		{
			if (!actor) return;

			std::lock_guard<std::mutex> lock(s_nodeMapMutex);
			s_lastHitNodes.erase(actor->formID);
		}

	private:

		inline static std::unordered_map<RE::FormID, std::string> s_lastHitNodes;
		inline static std::mutex s_nodeMapMutex;

		static bool IsActorValid(RE::Actor* actor)
		{
			if (!actor) return false;

			if (ModData::ActorTypeGhost && actor->HasKeyword(ModData::ActorTypeGhost)) return false;

			auto* actorBase = actor->GetActorBase();
			if (!actorBase) return false;

			if (!actorBase->Bleeds()) return false;
			if (actorBase->IsGhost()) return false;

			return true;
		}

		static float GetMaxRadius(RE::Actor* actor)
		{
			auto* actorRace = actor->GetRace();
			if (!actorRace) return 0.0f;

			auto* actorBase = actor->GetActorBase();
			if (!actorBase) return 0.0f;

			switch (actorBase->GetSex()) {
			case RE::SEX::kFemale:
				return actorRace->data.height[RE::SEX::kFemale] * actorRace->data.weight[RE::SEX::kFemale] * actorRace->data.baseMass;
			default:
				return actorRace->data.height[RE::SEX::kMale] * actorRace->data.weight[RE::SEX::kMale] * actorRace->data.baseMass;
			}
		}

		static RE::NiAVObject* GetCachedNodeForActor(RE::Actor* actor)
		{
			if (!actor) return {};

			std::lock_guard<std::mutex> lock(s_nodeMapMutex);

			std::string nodeName = "";
			auto it = s_lastHitNodes.find(actor->formID);
			if (it != s_lastHitNodes.end()) nodeName = it->second;

			return !nodeName.empty() ? actor->GetNodeByName(nodeName) : nullptr;
		}
	};
};
