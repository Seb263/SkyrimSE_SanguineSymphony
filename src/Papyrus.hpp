#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Utils/ModUtils.hpp"

namespace Papyrus
{
	std::vector<uint32_t> GetVersion(RE::StaticFunctionTag*)
	{
		using namespace SKSE;
        const auto* plugin = PluginDeclaration::GetSingleton();
        auto version = plugin->GetVersion();

        uint32_t versionMajor = plugin->GetVersion().major();
        uint32_t versionMinor = plugin->GetVersion().minor();
        uint32_t versionPatch = plugin->GetVersion().patch();

		std::vector<uint32_t> versionVector;
		versionVector.push_back(versionMajor);
		versionVector.push_back(versionMinor);
		versionVector.push_back(versionPatch);

		return versionVector;
	}

	bool GetIniValueBool(RE::StaticFunctionTag*, const RE::BSFixedString path, const bool defaultValue = false)
	{
		return SettingsIni::SettingsManager::GetSingleton().GetValue<bool>(path.c_str(), defaultValue);
	}

	float GetIniValueFloat(RE::StaticFunctionTag*, const RE::BSFixedString path, const float defaultValue = 0.0f)
	{ 
		return SettingsIni::SettingsManager::GetSingleton().GetValue<float>(path.c_str(), defaultValue);
	}

	int GetIniValueInt(RE::StaticFunctionTag*, const RE::BSFixedString path, const int defaultValue = 0)
	{
		return SettingsIni::SettingsManager::GetSingleton().GetValue<int>(path.c_str(), defaultValue);
	}

	RE::BSFixedString GetIniValueString(RE::StaticFunctionTag*, const RE::BSFixedString path, const RE::BSFixedString defaultValue = "")
	{
		return RE::BSFixedString(SettingsIni::SettingsManager::GetSingleton().GetValue<std::string>(path.c_str(), std::string(defaultValue.c_str())));
	}

	bool GetDefaultIniValueBool(RE::StaticFunctionTag*, const RE::BSFixedString path, const bool fallback = false)
	{
		return SettingsIni::SettingsManager::GetSingleton().GetDefaultValue<bool>(path.c_str(), fallback);
	}

	float GetDefaultIniValueFloat(RE::StaticFunctionTag*, const RE::BSFixedString path, const float fallback = 0.0f)
	{
		return SettingsIni::SettingsManager::GetSingleton().GetDefaultValue<float>(path.c_str(), fallback);
	}

	int GetDefaultIniValueInt(RE::StaticFunctionTag*, const RE::BSFixedString path, const int fallback = 0)
	{
		return SettingsIni::SettingsManager::GetSingleton().GetDefaultValue<int>(path.c_str(), fallback);
	}

	RE::BSFixedString GetDefaultIniValueString(RE::StaticFunctionTag*, const RE::BSFixedString path, const RE::BSFixedString fallback = "")
	{
		return RE::BSFixedString(SettingsIni::SettingsManager::GetSingleton().GetDefaultValue<std::string>(path.c_str(), std::string(fallback.c_str())));
	}

	bool SetIniValueBool(RE::StaticFunctionTag*, const RE::BSFixedString path, const bool value)
	{
		return SettingsIni::SettingsManager::GetSingleton().SetValue(path.c_str(), value);
	}

	bool SetIniValueFloat(RE::StaticFunctionTag*, const RE::BSFixedString path, const float value)
	{
		return SettingsIni::SettingsManager::GetSingleton().SetValue(path.c_str(), value);
	}

	bool SetIniValueInt(RE::StaticFunctionTag*, const RE::BSFixedString path, const int value)
	{
		return SettingsIni::SettingsManager::GetSingleton().SetValue(path.c_str(), value);
	}

	bool SetIniValueString(RE::StaticFunctionTag*, const RE::BSFixedString path, const RE::BSFixedString value)
	{
		return SettingsIni::SettingsManager::GetSingleton().SetValue(path.c_str(), std::string(value.c_str()));
	}

	void RequestRuntimeUpdate(RE::StaticFunctionTag*)
	{
		SettingsIni::SettingsManager::GetSingleton().ReadSettings();
		SettingsIni::SettingsManager::GetSingleton().SyncToGlobals();

		ModUtils::ApplyRuntimeSettings();
	}

	bool ShouldIgnoreMaintenanceChecks(RE::StaticFunctionTag*)
	{
		return SettingsIni::bGeneral_ShouldIgnoreMaintenanceChecks;
	}

	bool BindPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
	{
		vm->RegisterFunction("GetVersion", "SanguineSymphony", GetVersion);
		vm->RegisterFunction("GetIniValueBool", "SanguineSymphony", GetIniValueBool);
		vm->RegisterFunction("GetIniValueFloat", "SanguineSymphony", GetIniValueFloat);
		vm->RegisterFunction("GetIniValueInt", "SanguineSymphony", GetIniValueInt);
		vm->RegisterFunction("GetIniValueString", "SanguineSymphony", GetIniValueString);
		vm->RegisterFunction("GetDefaultIniValueBool", "SanguineSymphony", GetDefaultIniValueBool);
		vm->RegisterFunction("GetDefaultIniValueFloat", "SanguineSymphony", GetDefaultIniValueFloat);
		vm->RegisterFunction("GetDefaultIniValueInt", "SanguineSymphony", GetDefaultIniValueInt);
		vm->RegisterFunction("GetDefaultIniValueString", "SanguineSymphony", GetDefaultIniValueString);
		vm->RegisterFunction("SetIniValueBool", "SanguineSymphony", SetIniValueBool);
		vm->RegisterFunction("SetIniValueFloat", "SanguineSymphony", SetIniValueFloat);
		vm->RegisterFunction("SetIniValueInt", "SanguineSymphony", SetIniValueInt);
		vm->RegisterFunction("SetIniValueString", "SanguineSymphony", SetIniValueString);
		vm->RegisterFunction("RequestRuntimeUpdate", "SanguineSymphony", RequestRuntimeUpdate);
		vm->RegisterFunction("ShouldIgnoreMaintenanceChecks", "SanguineSymphony", ShouldIgnoreMaintenanceChecks);
		return true;
	}
};
