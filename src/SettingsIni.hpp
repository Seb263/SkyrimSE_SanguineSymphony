#pragma once

#include "DataHandler.hpp"

#include "Utils/GlobalValueUtils.hpp"

namespace SettingsIni
{
	// Initialization
	inline int iGeneral_VerboseMode = 1;
	inline bool bGeneral_ShouldIgnoreMaintenanceChecks = false;

	// DynamicImpact
	inline bool bDynamicImpact_Status = true;
	inline bool bDynamicImpact_ImmersiveSounds = true;
	inline bool bDynamicImpact_ExtraImpactEffects = true;
	inline bool bDynamicImpact_SparksStatus = true;
	inline float fDynamicImpact_SparksChances = 80.0f;

	inline bool bDynamicImpact_GoreSounds_LowHealth = true;
	inline bool bDynamicImpact_GoreSounds_Dying = true;
	inline bool bDynamicImpact_GoreSounds_Corpses = true;

	inline float fDynamicImpact_Unarmored_LightThreshold = 100.0f;
	inline float fDynamicImpact_Unarmored_ModerateThreshold = 80.0f;
	inline float fDynamicImpact_Unarmored_HeavyThreshold = 35.0f;
	inline bool bDynamicImpact_Unarmored_ArrowCanPierce = true;
	inline float fDynamicImpact_Unarmored_PierceThreshold = 5.0f;

	inline float fDynamicImpact_LightArmor_LightThreshold = 75.0f;
	inline float fDynamicImpact_LightArmor_ModerateThreshold = 50.0f;
	inline float fDynamicImpact_LightArmor_HeavyThreshold = 20.0f;
	inline bool bDynamicImpact_LightArmor_ArrowCanPierce = true;
	inline float fDynamicImpact_LightArmor_PierceThreshold = 15.0f;

	inline float fDynamicImpact_HeavyArmor_LightThreshold = 60.0f;
	inline float fDynamicImpact_HeavyArmor_ModerateThreshold = 30.0f;
	inline float fDynamicImpact_HeavyArmor_HeavyThreshold = 15.0f;
	inline bool bDynamicImpact_HeavyArmor_ArrowCanPierce = true;
	inline float fDynamicImpact_HeavyArmor_PierceThreshold = 30.0f;

	// BloodSpray
	inline bool bBloodSpray_NPC = true;
	inline bool bBloodSpray_Insect = true;
	inline bool bBloodSpray_Automaton = true;
	inline float fBloodSpray_Chances = 80.0f;
	inline bool bBloodSpray_Trailing = true;
	inline bool bBloodSpray_Sounds = true;

	// Bloodpools
	inline bool bBloodpools_Status = true;
	inline float fBloodpools_Chances = 80.0f;
	inline bool bBloodpools_EnableForBlades = true;
	inline bool bBloodpools_EnableForBlunt = true;
	inline bool bBloodpools_EnableForRanged = true;
	inline bool bBloodpools_EnableForUnarmed = true;
	inline bool bBloodpools_EnableForMagic = true;

	inline bool bBloodpools_DefaultStatus = true;
	inline float fBloodpools_Default_ScaleMin = 1.0f;
	inline float fBloodpools_Default_ScaleMax = 1.5f;
	inline float fBloodpools_Default_DurationMin = 7.0f;
	inline float fBloodpools_Default_DurationMax = 10.0f;

	inline bool bBloodpools_InsectStatus = true;
	inline float fBloodpools_Insect_ScaleMin = 1.0f;
	inline float fBloodpools_Insect_ScaleMax = 1.5f;
	inline float fBloodpools_Insect_DurationMin = 7.0f;
	inline float fBloodpools_Insect_DurationMax = 10.0f;

	inline bool bBloodpools_AutomatonStatus = true;
	inline float fBloodpools_Automaton_ScaleMin = 1.0f;
	inline float fBloodpools_Automaton_ScaleMax = 1.5f;
	inline float fBloodpools_Automaton_DurationMin = 7.0f;
	inline float fBloodpools_Automaton_DurationMax = 10.0f;

	// LetalStrikes
	inline bool bLetalStrikes_Status = true;
	inline bool bLetalStrikes_PlayerOnly = false;
	inline bool bLetalStrikes_LatestEnemy = true;
	inline float fLetalStrikes_Chances = 100.0f;
	inline int iLetalStrikes_Method = 0;

	inline float fLetalStrikes_Strength_OneHandSword = 50.0f;
	inline float fLetalStrikes_Strength_TwoHandSword = 70.0f;
	inline float fLetalStrikes_Strength_OneHandAxe = 60.0f;
	inline float fLetalStrikes_Strength_TwoHandAxe = 70.0f;
	inline float fLetalStrikes_Strength_OneHandMace = 60.0f;
	inline float fLetalStrikes_Strength_TwoHandMace = 80.0f;
	inline float fLetalStrikes_Strength_Dagger = 30.0f;
	inline float fLetalStrikes_Strength_Ranged = 70.0f;
	inline float fLetalStrikes_Strength_Magic = 70.0f;
	inline float fLetalStrikes_Strength_HandToHand = 40.0f;
	inline float fLetalStrikes_Strength_Beast = 70.0f;
	inline float fLetalStrikes_Strength_Other = 40.0f;

	// DeathEffect
	inline bool bDeathEffect_Status = true;
	inline bool bDeathEffect_IfBlocked = true;
	inline bool bDeathEffect_IfKillmove = true;
	inline bool bDeathEffect_LatestEnemy = true;
	inline bool bDeathEffect_OnlyHigherLevel = true;
	inline int iDeathEffect_LevelDifference = 0;
	inline float fDeathEffect_Chances = 100.0f;
	inline int iDeathEffect_IMODEffect = 1;
	inline int iDeathEffect_SoundEffect = 1;
	inline float fDeathEffect_SoundVolume = 1.0f;
	inline bool bDeathEffect_SlowTimeStatus = true;
	inline float fDeathEffect_SlowTimeFactor = 0.35f;
	inline float fDeathEffect_SlowTimeDuration = 1.5f;

	// Misc
	inline bool bMisc_Decals_EnforceMinimum = true;
	inline float fMisc_Decals_SkinLifetime = 300.0f;
	inline int iMisc_Decals_MaxPerActor = 60;
	inline bool bMisc_Decals_MultiLayering = true;

	inline float fMisc_ScreenSplatterDuration = 20.0f;
	inline bool bMisc_HeadshotDeflection = true;
	inline bool bMisc_ArrowAlwaysPiercesOnDeath = true;

	inline bool bMisc_SSEFixesWorkaround = true;

	class SettingsManager
	{
	public:
		static SettingsManager& GetSingleton()
		{
			static SettingsManager instance;
			return instance;
		}

		SettingsManager()
		{
			bindings = {
				// General
				{ "General", "iVerboseMode", &iGeneral_VerboseMode },
				{ "General", "bShouldIgnoreMaintenanceChecks", &bGeneral_ShouldIgnoreMaintenanceChecks },

				// DynamicImpact
				{ "DynamicImpact", "bStatus", &bDynamicImpact_Status, true },
				{ "DynamicImpact", "bImmersiveSounds", &bDynamicImpact_ImmersiveSounds, true },
				{ "DynamicImpact", "bExtraImpactEffects", &bDynamicImpact_ExtraImpactEffects, true },
				{ "DynamicImpact", "bSparksStatus", &bDynamicImpact_SparksStatus, true },
				{ "DynamicImpact", "fSparksChances", &fDynamicImpact_SparksChances, true },
				{ "DynamicImpact", "bGoreSounds_LowHealth", &bDynamicImpact_GoreSounds_LowHealth, true },
				{ "DynamicImpact", "bGoreSounds_Dying", &bDynamicImpact_GoreSounds_Dying, true },
				{ "DynamicImpact", "bGoreSounds_Corpses", &bDynamicImpact_GoreSounds_Corpses, true },
				{ "DynamicImpact", "fUnarmored_LightThreshold", &fDynamicImpact_Unarmored_LightThreshold, true },
				{ "DynamicImpact", "fUnarmored_ModerateThreshold", &fDynamicImpact_Unarmored_ModerateThreshold, true },
				{ "DynamicImpact", "fUnarmored_HeavyThreshold", &fDynamicImpact_Unarmored_HeavyThreshold, true },
				{ "DynamicImpact", "bUnarmored_ArrowCanPierce", &bDynamicImpact_Unarmored_ArrowCanPierce, true },
				{ "DynamicImpact", "fUnarmored_PierceThreshold", &fDynamicImpact_Unarmored_PierceThreshold, true },
				{ "DynamicImpact", "fLightArmor_LightThreshold", &fDynamicImpact_LightArmor_LightThreshold, true },
				{ "DynamicImpact", "fLightArmor_ModerateThreshold", &fDynamicImpact_LightArmor_ModerateThreshold, true },
				{ "DynamicImpact", "fLightArmor_HeavyThreshold", &fDynamicImpact_LightArmor_HeavyThreshold, true },
				{ "DynamicImpact", "bLightArmor_ArrowCanPierce", &bDynamicImpact_LightArmor_ArrowCanPierce, true },
				{ "DynamicImpact", "fLightArmor_PierceThreshold", &fDynamicImpact_LightArmor_PierceThreshold, true },
				{ "DynamicImpact", "fHeavyArmor_LightThreshold", &fDynamicImpact_HeavyArmor_LightThreshold, true },
				{ "DynamicImpact", "fHeavyArmor_ModerateThreshold", &fDynamicImpact_HeavyArmor_ModerateThreshold, true },
				{ "DynamicImpact", "fHeavyArmor_HeavyThreshold", &fDynamicImpact_HeavyArmor_HeavyThreshold, true },
				{ "DynamicImpact", "bHeavyArmor_ArrowCanPierce", &bDynamicImpact_HeavyArmor_ArrowCanPierce, true },
				{ "DynamicImpact", "fHeavyArmor_PierceThreshold", &fDynamicImpact_HeavyArmor_PierceThreshold, true },

				// BloodSpray
				{ "BloodSpray", "bNPC", &bBloodSpray_NPC, true },
				{ "BloodSpray", "bInsect", &bBloodSpray_Insect, true },
				{ "BloodSpray", "bAutomaton", &bBloodSpray_Automaton, true },
				{ "BloodSpray", "fChances", &fBloodSpray_Chances, true },
				{ "BloodSpray", "bTrailing", &bBloodSpray_Trailing, true },
				{ "BloodSpray", "bSounds", &bBloodSpray_Sounds, true },

				// Bloodpools
				{ "Bloodpools", "bStatus", &bBloodpools_Status },
				{ "Bloodpools", "fChances", &fBloodpools_Chances },
				{ "Bloodpools", "bEnableForBlades", &bBloodpools_EnableForBlades },
				{ "Bloodpools", "bEnableForBlunt", &bBloodpools_EnableForBlunt },
				{ "Bloodpools", "bEnableForRanged", &bBloodpools_EnableForRanged },
				{ "Bloodpools", "bEnableForUnarmed", &bBloodpools_EnableForUnarmed },
				{ "Bloodpools", "bEnableForMagic", &bBloodpools_EnableForMagic },
				{ "Bloodpools", "bDefaultStatus", &bBloodpools_DefaultStatus },
				{ "Bloodpools", "fDefault_ScaleMin", &fBloodpools_Default_ScaleMin },
				{ "Bloodpools", "fDefault_ScaleMax", &fBloodpools_Default_ScaleMax },
				{ "Bloodpools", "fDefault_DurationMin", &fBloodpools_Default_DurationMin },
				{ "Bloodpools", "fDefault_DurationMax", &fBloodpools_Default_DurationMax },
				{ "Bloodpools", "bInsectStatus", &bBloodpools_InsectStatus },
				{ "Bloodpools", "fInsect_ScaleMin", &fBloodpools_Insect_ScaleMin },
				{ "Bloodpools", "fInsect_ScaleMax", &fBloodpools_Insect_ScaleMax },
				{ "Bloodpools", "fInsect_DurationMin", &fBloodpools_Insect_DurationMin },
				{ "Bloodpools", "fInsect_DurationMax", &fBloodpools_Insect_DurationMax },
				{ "Bloodpools", "bAutomatonStatus", &bBloodpools_AutomatonStatus },
				{ "Bloodpools", "fAutomaton_ScaleMin", &fBloodpools_Automaton_ScaleMin },
				{ "Bloodpools", "fAutomaton_ScaleMax", &fBloodpools_Automaton_ScaleMax },
				{ "Bloodpools", "fAutomaton_DurationMin", &fBloodpools_Automaton_DurationMin },
				{ "Bloodpools", "fAutomaton_DurationMax", &fBloodpools_Automaton_DurationMax },

				// LetalStrikes
				{ "LetalStrikes", "bStatus", &bLetalStrikes_Status },
				{ "LetalStrikes", "bPlayerOnly", &bLetalStrikes_PlayerOnly },
				{ "LetalStrikes", "bLatestEnemy", &bLetalStrikes_LatestEnemy },
				{ "LetalStrikes", "fChances", &fLetalStrikes_Chances },
				{ "LetalStrikes", "iMethod", &iLetalStrikes_Method },
				{ "LetalStrikes", "fStrength_OneHandSword", &fLetalStrikes_Strength_OneHandSword },
				{ "LetalStrikes", "fStrength_TwoHandSword", &fLetalStrikes_Strength_TwoHandSword },
				{ "LetalStrikes", "fStrength_OneHandAxe", &fLetalStrikes_Strength_OneHandAxe },
				{ "LetalStrikes", "fStrength_TwoHandAxe", &fLetalStrikes_Strength_TwoHandAxe },
				{ "LetalStrikes", "fStrength_OneHandMace", &fLetalStrikes_Strength_OneHandMace },
				{ "LetalStrikes", "fStrength_TwoHandMace", &fLetalStrikes_Strength_TwoHandMace },
				{ "LetalStrikes", "fStrength_Dagger", &fLetalStrikes_Strength_Dagger },
				{ "LetalStrikes", "fStrength_Ranged", &fLetalStrikes_Strength_Ranged },
				{ "LetalStrikes", "fStrength_Magic", &fLetalStrikes_Strength_Magic },
				{ "LetalStrikes", "fStrength_HandToHand", &fLetalStrikes_Strength_HandToHand },
				{ "LetalStrikes", "fStrength_Beast", &fLetalStrikes_Strength_Beast },
				{ "LetalStrikes", "fStrength_Other", &fLetalStrikes_Strength_Other },

				// DeathEffect
				{ "DeathEffect", "bStatus", &bDeathEffect_Status },
				{ "DeathEffect", "bIfBlocked", &bDeathEffect_IfBlocked },
				{ "DeathEffect", "bIfKillmove", &bDeathEffect_IfKillmove },
				{ "DeathEffect", "bLatestEnemy", &bDeathEffect_LatestEnemy },
				{ "DeathEffect", "bOnlyHigherLevel", &bDeathEffect_OnlyHigherLevel },
				{ "DeathEffect", "iLevelDifference", &iDeathEffect_LevelDifference },
				{ "DeathEffect", "fChances", &fDeathEffect_Chances },
				{ "DeathEffect", "iIMODEffect", &iDeathEffect_IMODEffect },
				{ "DeathEffect", "iSoundEffect", &iDeathEffect_SoundEffect },
				{ "DeathEffect", "fSoundVolume", &fDeathEffect_SoundVolume },
				{ "DeathEffect", "bSlowTimeStatus", &bDeathEffect_SlowTimeStatus },
				{ "DeathEffect", "fSlowTimeFactor", &fDeathEffect_SlowTimeFactor },
				{ "DeathEffect", "fSlowTimeDuration", &fDeathEffect_SlowTimeDuration },

				// Misc
				{ "Misc", "bDecals_EnforceMinimum", &bMisc_Decals_EnforceMinimum },
				{ "Misc", "fDecals_SkinLifetime", &fMisc_Decals_SkinLifetime },
				{ "Misc", "iDecals_MaxPerActor", &iMisc_Decals_MaxPerActor },
				{ "Misc", "bDecals_MultiLayering", &bMisc_Decals_MultiLayering },
				{ "Misc", "fScreenSplatterDuration", &fMisc_ScreenSplatterDuration },
				{ "Misc", "bHeadshotDeflection", &bMisc_HeadshotDeflection, true },
				{ "Misc", "bArrowAlwaysPiercesOnDeath", &bMisc_ArrowAlwaysPiercesOnDeath, true },
				{ "Misc", "bSSEFixesWorkaround", &bMisc_SSEFixesWorkaround }
			};

			for (auto& bind : bindings) {
				std::visit([&](auto* ptr) {
					bind.defaultValue = *ptr;
				}, bind.var);
			}
		}

		bool ReadSettings()
		{
			std::wstring   wpath_str(path.begin(), path.end());
			const wchar_t* wpath = wpath_str.c_str();

			bool readStatus = false;

			logger::info("Trying to read INI file at path: {}", path);

			if (std::filesystem::exists(path)) {
				CSimpleIniA ini;
				ini.SetUnicode();

				if (ini.LoadFile(wpath) >= 0) {
					for (const auto& bind : bindings) {
						std::visit([&](auto* ptr) {
							using T = std::decay_t<decltype(*ptr)>;
							if constexpr (std::is_same_v<T, bool>) {
								*ptr = ini.GetBoolValue(bind.section, bind.key, *ptr);
							} else if constexpr (std::is_same_v<T, int>) {
								*ptr = static_cast<int>(ini.GetLongValue(bind.section, bind.key, *ptr));
							} else if constexpr (std::is_same_v<T, float>) {
								*ptr = static_cast<float>(ini.GetDoubleValue(bind.section, bind.key, *ptr));
							} else if constexpr (std::is_same_v<T, std::string>) {
								*ptr = ini.GetValue(bind.section, bind.key, ptr->c_str());
							}
						}, bind.var);
					}
					readStatus = true;
				} else {
					logger::error("Failed to load INI file at {}", path);
				}
			} else {
				logger::warn("INI file does not exist at {}", path);
			}

			// Clamping logic

			// General
			iGeneral_VerboseMode = std::clamp(iGeneral_VerboseMode, 0, 2);

			// DynamicImpact
			fDynamicImpact_SparksChances = std::clamp(fDynamicImpact_SparksChances, 0.0f, 100.0f);

			fDynamicImpact_Unarmored_LightThreshold = std::clamp(fDynamicImpact_Unarmored_LightThreshold, 0.0f, 100.0f);
			fDynamicImpact_Unarmored_ModerateThreshold = std::clamp(fDynamicImpact_Unarmored_ModerateThreshold, 0.0f, 100.0f);
			fDynamicImpact_Unarmored_HeavyThreshold = std::clamp(fDynamicImpact_Unarmored_HeavyThreshold, 0.0f, 100.0f);
			fDynamicImpact_Unarmored_PierceThreshold = std::clamp(fDynamicImpact_Unarmored_PierceThreshold, 0.0f, 100.0f);

			fDynamicImpact_LightArmor_LightThreshold = std::clamp(fDynamicImpact_LightArmor_LightThreshold, 0.0f, 100.0f);
			fDynamicImpact_LightArmor_ModerateThreshold = std::clamp(fDynamicImpact_LightArmor_ModerateThreshold, 0.0f, 100.0f);
			fDynamicImpact_LightArmor_HeavyThreshold = std::clamp(fDynamicImpact_LightArmor_HeavyThreshold, 0.0f, 100.0f);
			fDynamicImpact_LightArmor_PierceThreshold = std::clamp(fDynamicImpact_LightArmor_PierceThreshold, 0.0f, 100.0f);

			fDynamicImpact_HeavyArmor_LightThreshold = std::clamp(fDynamicImpact_HeavyArmor_LightThreshold, 0.0f, 100.0f);
			fDynamicImpact_HeavyArmor_ModerateThreshold = std::clamp(fDynamicImpact_HeavyArmor_ModerateThreshold, 0.0f, 100.0f);
			fDynamicImpact_HeavyArmor_HeavyThreshold = std::clamp(fDynamicImpact_HeavyArmor_HeavyThreshold, 0.0f, 100.0f);
			fDynamicImpact_HeavyArmor_PierceThreshold = std::clamp(fDynamicImpact_HeavyArmor_PierceThreshold, 0.0f, 100.0f);

			// BloodSpray
			fBloodSpray_Chances = std::clamp(fBloodSpray_Chances, 0.0f, 100.0f);

			// Bloodpools
			fBloodpools_Chances = std::clamp(fBloodpools_Chances, 0.0f, 100.0f);

			fBloodpools_Default_ScaleMin = std::clamp(fBloodpools_Default_ScaleMin, 0.25f, 2.5f);
			fBloodpools_Default_ScaleMax = std::clamp(fBloodpools_Default_ScaleMax, 0.25f, 2.5f);
			fBloodpools_Default_DurationMin = std::clamp(fBloodpools_Default_DurationMin, 1.0f, 25.0f);
			fBloodpools_Default_DurationMax = std::clamp(fBloodpools_Default_DurationMax, 1.0f, 25.0f);

			fBloodpools_Insect_ScaleMin = std::clamp(fBloodpools_Insect_ScaleMin, 0.25f, 2.5f);
			fBloodpools_Insect_ScaleMax = std::clamp(fBloodpools_Insect_ScaleMax, 0.25f, 2.5f);
			fBloodpools_Insect_DurationMin = std::clamp(fBloodpools_Insect_DurationMin, 1.0f, 25.0f);
			fBloodpools_Insect_DurationMax = std::clamp(fBloodpools_Insect_DurationMax, 1.0f, 25.0f);

			fBloodpools_Automaton_ScaleMin = std::clamp(fBloodpools_Automaton_ScaleMin, 0.25f, 2.5f);
			fBloodpools_Automaton_ScaleMax = std::clamp(fBloodpools_Automaton_ScaleMax, 0.25f, 2.5f);
			fBloodpools_Automaton_DurationMin = std::clamp(fBloodpools_Automaton_DurationMin, 1.0f, 25.0f);
			fBloodpools_Automaton_DurationMax = std::clamp(fBloodpools_Automaton_DurationMax, 1.0f, 25.0f);

			// Misc
			fMisc_Decals_SkinLifetime = std::clamp(fMisc_Decals_SkinLifetime, 30.0f, 500.0f);
			iMisc_Decals_MaxPerActor = std::clamp(iMisc_Decals_MaxPerActor, 10, 100);
			fMisc_ScreenSplatterDuration = std::clamp(fMisc_ScreenSplatterDuration, 0.0f, 60.0f);

			// LetalStrikes
			fLetalStrikes_Chances = std::clamp(fLetalStrikes_Chances, 0.0f, 100.0f);

			fLetalStrikes_Strength_OneHandSword = std::clamp(fLetalStrikes_Strength_OneHandSword, 0.0f, 300.0f);
			fLetalStrikes_Strength_TwoHandSword = std::clamp(fLetalStrikes_Strength_TwoHandSword, 0.0f, 300.0f);
			fLetalStrikes_Strength_OneHandAxe = std::clamp(fLetalStrikes_Strength_OneHandAxe, 0.0f, 300.0f);
			fLetalStrikes_Strength_TwoHandAxe = std::clamp(fLetalStrikes_Strength_TwoHandAxe, 0.0f, 300.0f);
			fLetalStrikes_Strength_OneHandMace = std::clamp(fLetalStrikes_Strength_OneHandMace, 0.0f, 300.0f);
			fLetalStrikes_Strength_TwoHandMace = std::clamp(fLetalStrikes_Strength_TwoHandMace, 0.0f, 300.0f);
			fLetalStrikes_Strength_Dagger = std::clamp(fLetalStrikes_Strength_Dagger, 0.0f, 300.0f);
			fLetalStrikes_Strength_Ranged = std::clamp(fLetalStrikes_Strength_Ranged, 0.0f, 300.0f);
			fLetalStrikes_Strength_Magic = std::clamp(fLetalStrikes_Strength_Magic, 0.0f, 300.0f);
			fLetalStrikes_Strength_HandToHand = std::clamp(fLetalStrikes_Strength_HandToHand, 0.0f, 300.0f);
			fLetalStrikes_Strength_Beast = std::clamp(fLetalStrikes_Strength_Beast, 0.0f, 300.0f);
			fLetalStrikes_Strength_Other = std::clamp(fLetalStrikes_Strength_Other, 0.0f, 300.0f);

			// DeathEffect
			iDeathEffect_LevelDifference = std::clamp(iDeathEffect_LevelDifference, -30, 30);
			fDeathEffect_Chances = std::clamp(fDeathEffect_Chances, 0.0f, 100.0f);
			fDeathEffect_SoundVolume = std::clamp(fDeathEffect_SoundVolume, 0.0f, 1.0f);
			fDeathEffect_SlowTimeFactor = std::clamp(fDeathEffect_SlowTimeFactor, 0.1f, 1.0f);
			fDeathEffect_SlowTimeDuration = std::clamp(fDeathEffect_SlowTimeDuration, 0.1f, 3.0f);

			// External data
			[&]() {
				using namespace ModData;
				debugVerboseMode = iGeneral_VerboseMode;
			}();

			return readStatus;
		}

		std::optional<std::variant<bool, int, float, std::string>> GetValueVariant(const std::string& key_section)
		{
			auto sep = key_section.rfind(':');
			if (sep == std::string::npos) {
				logger::error("GetValueVariant: Invalid key_section format: '{}'", key_section);
				return std::nullopt;
			}
			std::string section = key_section.substr(0, sep);
			std::string key     = key_section.substr(sep + 1);
			for (const auto& bind : bindings) {
				if (key == bind.key && section == bind.section) {
					if (auto v = std::get_if<bool*>        (&bind.var)) return **v;
					if (auto v = std::get_if<int*>         (&bind.var)) return **v;
					if (auto v = std::get_if<float*>       (&bind.var)) return **v;
					if (auto v = std::get_if<std::string*> (&bind.var)) return **v;
				}
			}
			return std::nullopt;
		}

		template <typename T>
		T GetValue(const std::string& key_section, const T& defaultValue = T{})
		{
			auto opt = GetValueVariant(key_section);
			if (!opt) {
				logger::error("GetValue: No binding found for '{}'", key_section);
				return defaultValue;
			}

			return std::visit([&](auto&& val) -> T {
				using V = std::decay_t<decltype(val)>;
				if constexpr (std::is_same_v<T, std::string>) {
					if constexpr (std::is_same_v<V, std::string>) return val;
				} else if constexpr (std::is_same_v<T, bool>) {
					if constexpr (std::is_same_v<V, bool>)  return val;
					if constexpr (std::is_same_v<V, int>)   return val != 0;
					if constexpr (std::is_same_v<V, float>) return val != 0.0f;
				} else if constexpr (std::is_same_v<T, int>) {
					if constexpr (std::is_same_v<V, int>)   return val;
					if constexpr (std::is_same_v<V, float>) return static_cast<int>(val);
					if constexpr (std::is_same_v<V, bool>)  return val ? 1 : 0;
				} else if constexpr (std::is_same_v<T, float>) {
					if constexpr (std::is_same_v<V, float>) return val;
					if constexpr (std::is_same_v<V, int>)   return static_cast<float>(val);
					if constexpr (std::is_same_v<V, bool>)  return val ? 1.0f : 0.0f;
				}
				logger::error("GetValue: Type mismatch for '{}'", key_section);
				return defaultValue;
			}, *opt);
		}

		std::optional<std::variant<bool, int, float, std::string>> GetDefaultValueVariant(const std::string& key_section)
		{
			auto sep = key_section.rfind(':');
			if (sep == std::string::npos) {
				logger::error("GetDefaultValueVariant: Invalid key_section format: '{}'", key_section);
				return std::nullopt;
			}
			std::string section = key_section.substr(0, sep);
			std::string key = key_section.substr(sep + 1);

			for (const auto& bind : bindings) {
				if (key == bind.key && section == bind.section) {
					return bind.defaultValue;
				}
			}
			return std::nullopt;
		}

		template <typename T>
		T GetDefaultValue(const std::string& key_section, const T& fallback = T{})
		{
			auto opt = GetDefaultValueVariant(key_section);
			if (!opt) {
				logger::error("GetDefaultValue: No binding found for '{}'", key_section);
				return fallback;
			}

			return std::visit([&](auto&& val) -> T {
				using V = std::decay_t<decltype(val)>;
				if constexpr (std::is_same_v<T, bool>) {
					if constexpr (std::is_same_v<V, bool>)  return val;
					if constexpr (std::is_same_v<V, int>)   return val != 0;
					if constexpr (std::is_same_v<V, float>) return val != 0.0f;
				} else if constexpr (std::is_same_v<T, int>) {
					if constexpr (std::is_same_v<V, int>)   return val;
					if constexpr (std::is_same_v<V, float>) return static_cast<int>(val);
					if constexpr (std::is_same_v<V, bool>)  return val ? 1 : 0;
				} else if constexpr (std::is_same_v<T, float>) {
					if constexpr (std::is_same_v<V, float>) return val;
					if constexpr (std::is_same_v<V, int>)   return static_cast<float>(val);
					if constexpr (std::is_same_v<V, bool>)  return val ? 1.0f : 0.0f;
				} else if constexpr (std::is_same_v<T, std::string>) {
					if constexpr (std::is_same_v<V, std::string>) return val;
				}
				logger::error("GetDefaultValue: Type mismatch for '{}'", key_section);
				return fallback;
			}, *opt);
		}

		template <typename T>
		bool SetValue(const std::string& key_section, const T& value)
		{
			auto sep = key_section.rfind(':');
			if (sep == std::string::npos) {
				logger::error("SetValue: Invalid key_section format: '{}'", key_section);
				return false;
			}

			std::string section = key_section.substr(0, sep);
			std::string key = key_section.substr(sep + 1);

			if (section.empty() || key.empty()) {
				logger::error("SetValue: Empty section or key in '{}'", key_section);
				return false;
			}

			for (auto& bind : bindings) {
				if (section == bind.section && key == bind.key) {
					bool matched = std::visit([&](auto* ptr) -> bool {
						using PtrType = std::decay_t<decltype(*ptr)>;
						if constexpr (std::is_same_v<PtrType, T>) {
							*ptr = value;
							return true;
						}
						return false;
					}, bind.var);

					if (!matched) {
						logger::error("SetValue: Type mismatch for '{}:{}'", section, key);
						return false;
					}

					CSimpleIniA ini;
					ini.SetUnicode();
					if (std::filesystem::exists(path)) ini.LoadFile(path.c_str());

					if constexpr (std::is_same_v<T, bool>) {
						ini.SetBoolValue(section.c_str(), key.c_str(), value);
					} else if constexpr (std::is_same_v<T, int>) {
						ini.SetLongValue(section.c_str(), key.c_str(), value);
					} else if constexpr (std::is_same_v<T, float>) {
						ini.SetDoubleValue(section.c_str(), key.c_str(), value);
					} else if constexpr (std::is_same_v<T, std::string>) {
						ini.SetValue(section.c_str(), key.c_str(), value.c_str());
					} else {
						return false;
					}

					if (ini.SaveFile(path.c_str()) < 0) {
						logger::error("SetValue: Failed to save INI file at '{}'", path);
						return false;
					}

					return true;
				}
			}

			logger::error("SetValue: No binding found for '{}:{}'", section, key);
			return false;
		}

		void SyncToGlobals()
		{
			for (const auto& bind : bindings) {
				if (!bind.syncGlobal) continue;
					
				const std::string id = GlobalValueUtils::MakeGlobalEditorID(prefix, std::string(bind.section) + "_" + bind.key);

				std::visit([&](auto* ptr) {
					using T = std::decay_t<decltype(*ptr)>;

					if constexpr (std::is_same_v<T, bool>) {
						GlobalValueUtils::MakeGlobalValue(id, static_cast<float>(*ptr));
					} else if constexpr (std::is_same_v<T, int>) {
						GlobalValueUtils::MakeGlobalValue(id, static_cast<int>(*ptr));
					} else if constexpr (std::is_same_v<T, float>) {
						GlobalValueUtils::MakeGlobalValue(id, *ptr);
					}
				}, bind.var);
			}

			constexpr auto SSEFixesPath = L"Data/DLLPlugins/FPSFixPlugin.dll";
			auto isSSEFixesPresent = [](const wchar_t* SSEFixesPath) -> bool {
				return std::filesystem::exists(SSEFixesPath);
			};

			if (bMisc_SSEFixesWorkaround && isSSEFixesPresent(SSEFixesPath)) return;

			GlobalValueUtils::RegisterCachedGlobals();
		}

	private:
		inline static std::string path = "Data/SKSE/Plugins/SanguineSymphony.ini";
		inline static std::string prefix = "SS";

		using IniValue = std::variant<bool*, int*, float*, std::string*>;

		struct IniBinding
		{
			const char* section;
			const char* key;
			IniValue var;
			bool syncGlobal = false;
			std::variant<bool, int, float, std::string> defaultValue;
		};

		std::vector<IniBinding> bindings;
	};
}
