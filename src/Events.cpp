#include "Events.h"

namespace Events
{
	RE::BSEventNotifyControl ModEventSink::ProcessEvent(const RE::TESLoadGameEvent* event, RE::BSTEventSource<RE::TESLoadGameEvent>*)
	{
		ModData::lastLoadPoint = std::chrono::steady_clock::now();
		ModData::previousCell = 0x0;

		ModCore::BloodPool::PurgeNodeMap();

		RE::BSTimer* bsTimer = RE::BSTimer::GetSingleton();
		if (!bsTimer) REPORT_AND_FAIL("bsTimer could not be initialized.");

		bsTimer->SetGlobalTimeMultiplier(1.0f, false);

		return continueEvent;
	}

	RE::BSEventNotifyControl ModEventSink::ProcessEvent(const RE::TESDeathEvent* event, RE::BSTEventSource<RE::TESDeathEvent>*)
	{
		if (event->dead) return continueEvent;

		RE::Actor* victim = event->actorDying && event->actorDying.get() ? event->actorDying->As<RE::Actor>() : nullptr;
		if (!victim) return continueEvent;

		TimeUtils::WaitAndCall(250ms, [victimHandle = victim->GetHandle()](TimeUtils::CallResult result, std::chrono::nanoseconds) {
			if (result != TimeUtils::CallResult::kEndDone) return true;
			
			auto* victim = MiscUtils::ResolveHandle<RE::Actor>(victimHandle);
			if (victim) ModCore::BloodPool::ProcessBloodpool(victim);

			return true;
		});

		return continueEvent;
	}
}
