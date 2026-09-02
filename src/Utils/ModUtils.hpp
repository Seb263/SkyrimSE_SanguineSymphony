#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Utils/MiscUtils.hpp"

class ModUtils
{
public:

	static inline void ApplyRuntimeSettings()
	{
		using namespace ModData;

		logger::info("Applying Runtime Settings...");

		[](const bool status) { // EnforceMinimumSettings
			if (!status) return;

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("fDecalLOD0:Display");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("fDecalLOD0:Display");

				if (setting) {
					if (setting->data.f < 8192.0f) setting->data.f = 8192.0f;
				} else logger::error("Failed to find fDecalLOD0:Display INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("bDisableAllGore:General");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("bDisableAllGore:General");

				if (setting) setting->data.b = false;
				else logger::error("Failed to find bDisableAllGore:General INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("bDecals:Decals");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("bDecals:Decals");

				if (setting) setting->data.b = true;
				else logger::error("Failed to find bDecals:Decals INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("bSkinnedDecals:Decals");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("bSkinnedDecals:Decals");

				if (setting) setting->data.b = true;
				else logger::error("Failed to find bSkinnedDecals:Decals INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("uMaxDecals:Decals");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("uMaxDecals:Decals");

				if (setting) {
					if (setting->data.u < 100) setting->data.u = 100;
				} else logger::error("Failed to find uMaxDecals:Decals INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("uMaxSkinDecals:Decals");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("uMaxSkinDecals:Decals");

				if (setting) {
					if (setting->data.u < 35) setting->data.u = 35;
				} else logger::error("Failed to find uMaxSkinDecals:Decals INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("uMaxSkinDecalPerActor:Decals");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("uMaxSkinDecalPerActor:Decals");

				if (setting) {
					if (setting->data.u < 20) setting->data.u = 20;
				} else logger::error("Failed to find uMaxSkinDecalPerActor:Decals INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("iMaxDecalsPerFrame:Display");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("iMaxDecalsPerFrame:Display");

				if (setting) {
					if (setting->data.i < 10) setting->data.i = 10;
				} else logger::error("Failed to find iMaxDecalsPerFrame:Display INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("iMaxSkinDecalsPerFrame:Display");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("iMaxSkinDecalsPerFrame:Display");

				if (setting) {
					if (setting->data.i < 3) setting->data.i = 3;
				} else logger::error("Failed to find iMaxSkinDecalsPerFrame:Display INI setting.");
			}();

			[]() {
				auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("fDecalLifetime:Display");
				if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("fDecalLifetime:Display");

				if (setting) {
					if (setting->data.f < 30.0f) setting->data.f = 30.0f;
				} else logger::error("Failed to find fDecalLifetime:Display INI setting.");
			}();
		}(SettingsIni::bMisc_Decals_EnforceMinimum);

		[](const float duration) { // fBloodSplatterDuration
			if (!MiscUtils::SetGameSetting("fBloodSplatterDuration", duration)) {
				logger::error("Failed to change the value of the fBloodSplatterDuration setting.");
			}
		}(SettingsIni::fMisc_ScreenSplatterDuration);

		[](const float value) {  // fDecalLifetime
			auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("fDecalLifetime:Display");
			if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("fDecalLifetime:Display");

			if (setting) setting->data.f = value;
			else logger::error("Failed to find fDecalLifetime:Decals INI setting.");
		}(SettingsIni::fMisc_Decals_SkinLifetime);

		[](const int value) {  // uMaxSkinDecalPerActor
			auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("uMaxSkinDecalPerActor:Decals");
			if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("uMaxSkinDecalPerActor:Decals");

			if (setting) setting->data.u = value;
			else logger::error("Failed to find uMaxSkinDecalPerActor:Decals INI setting.");
		}(SettingsIni::iMisc_Decals_MaxPerActor);

		[](const bool status) { // bForceAllDecals
			auto setting = RE::INISettingCollection::GetSingleton()->GetSetting("bForceAllDecals:Decals");
			if (!setting) setting = RE::INIPrefSettingCollection::GetSingleton()->GetSetting("bForceAllDecals:Decals");

			if (setting) setting->data.b = status;
			else logger::error("Failed to find bForceAllDecals:Decals INI setting.");
		}(SettingsIni::bMisc_Decals_MultiLayering);

		logger::info("Applying Runtime Settings: DONE");
	}

	static bool IsLatestEnemyAlive(RE::Actor* target, RE::Actor* aggressor)
	{
		if (!target || !aggressor) return false;
		
		int nb_hostiles = 0;

		const auto processCell = [&](RE::TESObjectCELL* cell) {
			if (!cell || !cell->IsAttached()) return;

			cell->ForEachReference([&](RE::TESObjectREFR* ref) -> RE::BSContainer::ForEachResult {
				if (!ref || ref->formType != RE::FormType::ActorCharacter || !ref->GetParentCell() || !ref->GetParentCell()->IsAttached() ||
					ref->GetDistance(aggressor) > 4096.0f) return RE::BSContainer::ForEachResult::kContinue;
			
				RE::Actor* actor = ref->As<RE::Actor>();
				if (!actor || actor == target || actor == aggressor || !actor->Is3DLoaded()) return RE::BSContainer::ForEachResult::kContinue;

				if (!actor->AsActorState() || !actor->AsActorState()->IsBleedingOut()) {
					if (actor->IsHostileToActor(aggressor) && actor->IsInCombat() && actor->RequestDetectionLevel(aggressor) > 1) {
						nb_hostiles++;
					}
				}
				
				return RE::BSContainer::ForEachResult::kContinue;
			});
		};

		ProcessGridCells(processCell);

		return (nb_hostiles < 1);
	}

	static void ProcessGridCells(const std::function<void(RE::TESObjectCELL*)>& processCell)
	{
		auto* tes = RE::TES::GetSingleton();
		if (!tes) return;

		if (auto* cell = tes->interiorCell; cell && cell->IsAttached()) {
			processCell(cell);
		} else {
			if (const auto gridLength = tes->gridCells ? tes->gridCells->length : 0; gridLength > 0) {
				for (std::uint32_t x = 0; x < gridLength; ++x) {
					for (std::uint32_t y = 0; y < gridLength; ++y) {
						auto* cell = tes->gridCells->GetCell(x, y);
						if (!cell || !cell->IsAttached()) continue;

						processCell(cell);
					}
				}
			}
		}
	}
};
