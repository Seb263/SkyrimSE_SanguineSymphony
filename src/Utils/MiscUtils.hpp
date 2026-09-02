#pragma once

class MiscUtils
{
	public:

	template <typename T = RE::TESObjectREFR, typename HandleT>
	static T* ResolveHandle(const HandleT& handle)
	{
		auto ptr = handle ? handle.get() : nullptr;
		if (!ptr) return nullptr;

		return ptr->As<T>();
	}

	static bool IsFormIDValid(const RE::FormID formID)
	{
		return (formID > 0x0 && formID < 0xFFFFFFFF);
	}

	template <typename T = RE::TESObjectREFR>
	static T* GetValidReference(RE::FormID formID, const bool extraChecks = false)
	{
		if (!MiscUtils::IsFormIDValid(formID)) return nullptr;
		return GetValidReference<T>(RE::TESForm::LookupByID<RE::TESObjectREFR>(formID), extraChecks);
	}

	template <typename T = RE::TESObjectREFR>
	static T* GetValidReference(RE::TESObjectREFR* ref, const bool extraChecks = false)
	{
		using namespace ModData;

		if (!ref || !ref->As<T>() || !MiscUtils::IsFormIDValid(ref->formID) || ref->IsDeleted())
			return nullptr;

		if (extraChecks) {
			if (ref->IsDisabled() || ref->IsMarkedForDeletion())
				return nullptr;
		}

		if constexpr (std::is_same_v<T, RE::Actor>) {
			auto* refActor = ref->As<RE::Actor>();
			if (!refActor || !ref->Is(RE::FormType::ActorCharacter))
				return nullptr;

			if (extraChecks && (refActor->GetActorRuntimeData().criticalStage != RE::ACTOR_CRITICAL_STAGE::kNone))
				return nullptr;
		}

		return ref->As<T>();
	}

	template <typename T>
	static T GetGlobalValue(const std::string& gvEditorID)
	{
		auto* form = RE::TESForm::LookupByEditorID<RE::TESGlobal>(gvEditorID.c_str());
		if (!form || !form->formID) {
			logger::warn("GetGlobalValue: Global \"{}\" not found", gvEditorID);
			return T{};
		}

		if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>) {
			return static_cast<T>(form->value);
		} else if constexpr (std::is_same_v<T, bool>) {
			return static_cast<T>(form->value > 0.0f);
		}

		return T{};
	}

	static bool SetGameSetting(const std::string& settingName, const std::variant<bool, float, int32_t, uint32_t, std::string>& newValue)
	{
		auto* gsc = RE::GameSettingCollection::GetSingleton();
		if (!gsc || settingName.empty()) return false;

		auto* setting = gsc->GetSetting(settingName.c_str());
		if (!setting) {
			logger::warn("SetGameSetting: setting \"{}\" not found", settingName);
			return false;
		}

		using SettingType = RE::Setting::Type;
		auto settingType = setting->GetType();

		switch (settingType) {
			case SettingType::kBool: if (auto value = std::get_if<bool>(&newValue)) { setting->data.b = *value; return true; } break;
			case SettingType::kFloat: if (auto value = std::get_if<float>(&newValue)) { setting->data.f = *value; return true; } break;
			case SettingType::kInteger: if (auto value = std::get_if<int32_t>(&newValue)) { setting->data.i = *value; return true; } break;
			case SettingType::kUnsignedInteger: if (auto value = std::get_if<uint32_t>(&newValue)) { setting->data.u = *value; return true; } break;
			case SettingType::kString:
				if (auto value = std::get_if<std::string>(&newValue)) {
					free(setting->data.s);
					setting->data.s = _strdup(value->c_str());
					return true;
				} break;
			default: return false;
		}

		return false;
	}

	static REL::Version GetPluginVersion(const char* a_moduleName)
	{
		const auto handle = GetModuleHandleA(a_moduleName);
		if (!handle) return REL::Version{};

		char path[MAX_PATH]{};
		if (!GetModuleFileNameA(handle, path, MAX_PATH)) return REL::Version{};

		DWORD dummy = 0;
		const DWORD size = GetFileVersionInfoSizeA(path, &dummy);
		if (size == 0) return REL::Version{};

		std::vector<std::byte> data(size);
		if (!GetFileVersionInfoA(path, 0, size, data.data())) return REL::Version{};

		VS_FIXEDFILEINFO* fileInfo = nullptr;
		UINT fileInfoLen = 0;
		if (!VerQueryValueA(data.data(), "\\", reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoLen)) return REL::Version{};
		if (!fileInfo) return REL::Version{};

		return REL::Version{
			HIWORD(fileInfo->dwFileVersionMS),
			LOWORD(fileInfo->dwFileVersionMS),
			HIWORD(fileInfo->dwFileVersionLS),
			LOWORD(fileInfo->dwFileVersionLS)
		};
	}

	static float GetRandomNumber(float min = 0.0f, float max = 1.0f)
	{
		static std::mt19937 generator(std::random_device{}());
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(generator);
	}
};
