#pragma once

#include "DataHandler.hpp"

class GlobalValueUtils
{
	public:

	static RE::TESGlobal* FindGlobal(const std::string& gvEditorID)
    {
        std::shared_lock lock(s_globalMutex);
        auto it = s_globalCache.find(gvEditorID);

		if (it == s_globalCache.end()) {
			lock.unlock();
			if (auto* existing = RE::TESForm::LookupByEditorID<RE::TESGlobal>(gvEditorID.c_str()); existing && existing->formID) {
				std::unique_lock uniqueLock(s_globalMutex);
				s_globalCache.emplace(gvEditorID, existing);
				it = s_globalCache.find(gvEditorID);
				return it != s_globalCache.end() ? it->second : nullptr;
			}
			return nullptr;
		}

        return it->second;
    }

    template <typename T>
    static T GetGlobalValue(const std::string& gvEditorID)
    {
        auto* form = FindGlobal(gvEditorID);
        if (!form) {
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

	static bool MakeGlobalValue(const std::string& gvEditorID, const std::variant<bool, int, float>& value)
	{
		if (gvEditorID.empty()) return false;

        if (auto* existing = FindGlobal(gvEditorID)) {
            return SetGlobalValue(existing, value);
        }

        const auto globalFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESGlobal>();
        auto* globalValue = globalFactory ? globalFactory->Create() : nullptr;
        if (!globalValue) {
            logger::error("MakeGlobalValue: Failed to create \"{}\"", gvEditorID);
            return false;
        }

        globalValue->SetFormEditorID(gvEditorID.c_str());
        globalValue->type = std::holds_alternative<float>(value) ? RE::TESGlobal::Type::kFloat : RE::TESGlobal::Type::kShort;
        globalValue->formFlags = RE::TESGlobal::RecordFlags::kConstant;
        ModData::TESdataHandler->AddFormToDataHandler(globalValue);

		{
			std::unique_lock lock(s_globalMutex);
			s_globalCache.emplace(gvEditorID, globalValue);
		}

		TRACE("MakeGlobalValue: Created \"{}\" ({:08X})", gvEditorID, globalValue->formID);

		return SetGlobalValue(globalValue, value);
	}

	static bool SetGlobalValue(RE::TESGlobal* form, const std::variant<bool, int, float>& newValue)
    {
        if (!form) return false;

        form->value = std::holds_alternative<bool>(newValue) ? static_cast<float>(std::get<bool>(newValue)) :
            std::holds_alternative<int>(newValue) ? static_cast<float>(std::get<int>(newValue)) :
            std::get<float>(newValue);
        return true;
    }

	static bool SetGlobalValue(const std::string& gvEditorID, const std::variant<bool, int, float>& newValue)
    {
        auto* form = FindGlobal(gvEditorID);
        if (!form) {
            logger::warn("SetGlobalValue: Global \"{}\" not found", gvEditorID);
            return false;
        }

        return SetGlobalValue(form, newValue);
    }

	static std::string MakeGlobalEditorID(const std::string& prefix, const std::string& name)
	{
		std::string result;
		bool lastWasUnderscore = false;

		for (char c : prefix + "_" + name) {
			char out = (std::isalnum((unsigned char)c) || c == '_') ? c : '_';
			if (out == '_' && lastWasUnderscore) continue;
			lastWasUnderscore = (out == '_');
			result += out;
		}

		auto notUnderscore = [](char c){ return c != '_'; };
		result.erase(result.begin(), std::find_if(result.begin(), result.end(), notUnderscore));
		result.erase(std::find_if(result.rbegin(), result.rend(), notUnderscore).base(), result.end());

		return result;
	}

	static void RegisterCachedGlobals()
	{
		std::shared_lock lock(s_globalMutex);
		
		if (s_globalCache.empty()) return;

		auto [formMap, formLock] = RE::TESForm::GetAllForms();
		auto [editorMap, editorLock] = RE::TESForm::GetAllFormsByEditorID();

		if (formMap) {
			RE::BSWriteLockGuard l{ formLock };
			for (auto& [editorID, form] : s_globalCache) {
				if (!form) continue;
				formMap->emplace(form->formID, form);
			}
		}

		if (editorMap) {
			RE::BSWriteLockGuard l{ editorLock };
			for (auto& [editorID, form] : s_globalCache) {
				if (!form) continue;
				editorMap->emplace(RE::BSFixedString(editorID.c_str()), form);
			}
		}
	}

	inline static std::shared_mutex s_globalMutex;
	inline static std::unordered_map<std::string, RE::TESGlobal*> s_globalCache;
};
