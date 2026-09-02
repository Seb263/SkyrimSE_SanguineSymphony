#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Core/Structure.h"
#include "Core/Features/BloodPool.hpp"
#include "Core/Features/DeathEffect.hpp"

namespace ModCore
{
	using namespace CoreStructure;

	class Main
	{

	public:

		static void ProcessDeferredHit(const RuntimeHitContext context)
		{
			auto* victim = MiscUtils::GetValidReference<RE::Actor>(context.victimFormID);
			if (!victim) return;

			using ActorState = Filter::StateFilter;

			bool alreadyHadHitNode = false;
			BloodPool::RecordLastHitNode(victim, context, alreadyHadHitNode);

			if (context.state == ActorState::kKillmove || context.state == ActorState::kDying) {
				DeathEffect::ApplyEffects(victim, context);
			}
			
			TimeUtils::WaitUntilRagdollReady(victim, [context, alreadyHadHitNode](RE::TESObjectREFR* objectRef, const bool result) {
				if (!result || !objectRef) return;
				
				RE::Actor* victim = objectRef->As<RE::Actor>();
				if (!victim) return;

				if (context.state == ActorState::kDying) {
					DeathEffect::ApplyImpulses(victim, context);
				} else if (!alreadyHadHitNode && context.state == ActorState::kDead) {
					BloodPool::ProcessBloodpool(victim);
				}
			});
		}

	private:

	};
}
