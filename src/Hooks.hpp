#pragma once

#include "DataHandler.hpp"
#include "SettingsIni.hpp"

#include "Core/Features/BloodPool.hpp"

#include "Utils/TimeUtils.hpp"

namespace Events
{
	using namespace ModData;
	using namespace ModCore;

	class Hooks
	{
	public:
		// Initialization of hooks and template functions
		static void InstallHooks()
		{
			REL::Relocation<std::uintptr_t> character_vt{ RE::Character::VTABLE[0] };
			_ResurrectHandler = character_vt.write_vfunc(REL::Module::IsVR() ? 0x0AD : 0x0AB, ResurrectHookTemplate);
			logger::info("ResurrectHandler hooked at address: 0x{:X}", _ResurrectHandler.address());
		}

	private:

		static void ResurrectHookTemplate(RE::Character* a_this, bool a_resetInventory, bool a_attach3D)
		{
			if (a_this) {
				if (auto* actor = a_this->As<RE::Actor>()) {
					BloodPool::RemoveCachedNodeForActor(actor);
				}
			}

			_ResurrectHandler(a_this, a_resetInventory, a_attach3D);
		}
		static inline REL::Relocation<decltype(ResurrectHookTemplate)> _ResurrectHandler;
	};
};
