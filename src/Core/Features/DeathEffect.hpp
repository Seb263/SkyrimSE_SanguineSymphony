#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Core/Structure.h"

#include "Utils/MiscUtils.hpp"
#include "Utils/ModUtils.hpp"
#include "Utils/NativeUtils.hpp"
#include "Utils/NiUtils.hpp"
#include "Utils/TimeUtils.hpp"

namespace ModCore
{
	using namespace CoreStructure;

	class DeathEffect
	{
	public:
		static void ApplyEffects(RE::Actor* victimRef, const RuntimeHitContext& context)
		{
			using namespace ModData;

			if (!victimRef) return;

			RE::Actor* attackerRef = RE::TESForm::LookupByID<RE::Actor>(context.attackerFormID);
			if (!attackerRef || attackerRef->formType != RE::FormType::ActorCharacter) return;
		
			if (!SettingsIni::bDeathEffect_Status || !attackerRef->IsPlayerRef()) return;
			if ((SettingsIni::fDeathEffect_Chances / 100.0f) < MiscUtils::GetRandomNumber()) return;
			if (!SettingsIni::bDeathEffect_IfKillmove && context.state == Filter::StateFilter::kKillmove) return;
			if (SettingsIni::bDeathEffect_LatestEnemy && !ModUtils::IsLatestEnemyAlive(victimRef, attackerRef)) return;
			if (!SettingsIni::bDeathEffect_IfBlocked && context.blocked != Filter::BlockedFilter::kNo) return;

			if (SettingsIni::bDeathEffect_OnlyHigherLevel) {
				auto playerLevel = attackerRef->GetLevel();
				auto victimLevel = victimRef->GetLevel();

				if (victimLevel < playerLevel + SettingsIni::iDeathEffect_LevelDifference) return;
			}

			RE::TESImageSpaceModifier* IMODEffect = nullptr;
			switch (SettingsIni::iDeathEffect_IMODEffect) {
				case 1: IMODEffect = DeathEventIMOD_Classic; break;
				case 2: IMODEffect = DeathEventIMOD_Mono; break;
				case 3: IMODEffect = DeathEventIMOD_Negative; break;
				case 4: {
					const int randomChoice = rand() % 3 + 1;
					switch (randomChoice) {
						case 1: IMODEffect = DeathEventIMOD_Classic; break;
						case 2: IMODEffect = DeathEventIMOD_Mono; break;
						case 3: IMODEffect = DeathEventIMOD_Negative; break;
					}
					break;
				}
			}

			if (IMODEffect) RE::ImageSpaceModifierInstanceForm::Trigger(IMODEffect, 1.0f, nullptr);

			RE::TESSound* soundEffect = nullptr;
			switch (SettingsIni::iDeathEffect_SoundEffect) {
				case 1: soundEffect = DeathEventSound_Subtle; break;
				case 2: soundEffect = DeathEventSound_DF; break;
			}

			if (soundEffect && soundEffect->descriptor) {
				NativeUtils::PlaySound(soundEffect->descriptor, SettingsIni::fDeathEffect_SoundVolume);
			}

			[&]() {
				if (!SettingsIni::bDeathEffect_SlowTimeStatus) return;
				if (context.state == Filter::StateFilter::kKillmove) return;

				if (!REL::Module::IsVR()) { // Crash with HasEffectWithArchetype on VR (MagicTarget.cpp:54)
					if (auto* player = RE::PlayerCharacter::GetSingleton()) {
						if (auto* playerMagicTarget = player->AsMagicTarget()) {
							if (playerMagicTarget->HasEffectWithArchetype(RE::EffectArchetypes::ArchetypeID::kSlowTime)) return;
						}
					}
				}

				float slowTimeFactor = SettingsIni::fDeathEffect_SlowTimeFactor;
				float slowTimeDuration = SettingsIni::fDeathEffect_SlowTimeDuration;

				if (slowTimeFactor > 0.0f && slowTimeDuration > 0.0f) {
					RE::BSTimer* bsTimer = RE::BSTimer::GetSingleton();
					if (!bsTimer) REPORT_AND_FAIL("bsTimer could not be initialized.");
			
					bsTimer->SetGlobalTimeMultiplier(slowTimeFactor, false);

					TimeUtils::WaitAndCall(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<float>(slowTimeDuration)),
						[](TimeUtils::CallResult result, std::chrono::nanoseconds) {
						if (TimeUtils::IsEnd(result)) {
							RE::BSTimer* bsTimer = RE::BSTimer::GetSingleton();
							if (!bsTimer) REPORT_AND_FAIL("bsTimer could not be initialized.");
			
							bsTimer->SetGlobalTimeMultiplier(1.0f, false);
						}
						return true;
					});
				}
			}();

			// May need a bridge for SS_DeathEffect_DF_GV
		}

		static void ApplyImpulses(RE::Actor* victimRef, const RuntimeHitContext& context)
		{
			using namespace ModData;

			RE::Actor* attackerRef = RE::TESForm::LookupByID<RE::Actor>(context.attackerFormID);
			if (!attackerRef || attackerRef->formType != RE::FormType::ActorCharacter) return;

			if (!SettingsIni::bLetalStrikes_Status) return;
			if (SettingsIni::fLetalStrikes_Chances / 100.0f < MiscUtils::GetRandomNumber()) return;
			if (SettingsIni::bLetalStrikes_LatestEnemy && !ModUtils::IsLatestEnemyAlive(victimRef, attackerRef)) return;
			if (SettingsIni::bLetalStrikes_PlayerOnly && !attackerRef->IsPlayerRef()) return;

			RE::NiAVObject* closestNode = nullptr;
			if (!context.bipedEntry.bipedNode.empty()) closestNode = victimRef->GetNodeByName(context.bipedEntry.bipedNode);

			if (!closestNode) return;

			float impulse = 0.0f;
			using WeaponType = Filter::WeaponType;
			switch (context.weaponType) {
				case WeaponType::kHandToHand:   impulse = SettingsIni::fLetalStrikes_Strength_HandToHand; break;
				case WeaponType::kBeast:        impulse = SettingsIni::fLetalStrikes_Strength_Beast; break;
				case WeaponType::kOneHandSword: impulse = SettingsIni::fLetalStrikes_Strength_OneHandSword; break;
				case WeaponType::kTwoHandSword: impulse = SettingsIni::fLetalStrikes_Strength_TwoHandSword; break;
				case WeaponType::kOneHandAxe:   impulse = SettingsIni::fLetalStrikes_Strength_OneHandAxe; break;
				case WeaponType::kTwoHandAxe:   impulse = SettingsIni::fLetalStrikes_Strength_TwoHandAxe; break;
				case WeaponType::kOneHandMace:  impulse = SettingsIni::fLetalStrikes_Strength_OneHandMace; break;
				case WeaponType::kTwoHandMace:  impulse = SettingsIni::fLetalStrikes_Strength_TwoHandMace; break;
				case WeaponType::kDagger:       impulse = SettingsIni::fLetalStrikes_Strength_Dagger; break;
				case WeaponType::kRanged:       impulse = SettingsIni::fLetalStrikes_Strength_Ranged; break;
				case WeaponType::kMagic:        impulse = SettingsIni::fLetalStrikes_Strength_Magic; break;
				default:                        impulse = SettingsIni::fLetalStrikes_Strength_Other; break;
			}

			float impulsePower = (impulse * (context.attack == Filter::AttackFilter::kPower ? 1.5f : 1.0f));
			bool ignoreMass = false;
		
			switch (SettingsIni::iLetalStrikes_Method) {
			case 0:
				if (auto* rootObject = victimRef->Get3D()) {
					impulsePower *= rootObject->GetMass() / 128.0f;
					ignoreMass = true;
				}
				break;
			case 1:
				ignoreMass = true;
				break;
			case 2:
				impulsePower /= 4.0f;
				ignoreMass = false;
				break;
			}

			NiUtils::ApplyImpulseToRigidBody(closestNode, context.hitDirection, impulsePower, 0.0f, ignoreMass);
		}
	};
};
