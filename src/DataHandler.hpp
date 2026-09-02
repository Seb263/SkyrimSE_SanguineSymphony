#pragma once

#include "API/CIF-API.h"
#include "API/DBF-API.h"
#include "API/NGD-API.h"

namespace ModData
{
	constexpr std::string_view MOD_NAME = "Sanguine Symphony";
	constexpr std::string_view PLUGIN_NAME = "Sanguine Symphony.esp";

	inline auto lastLoadPoint = std::chrono::steady_clock::now();
	inline std::atomic<RE::FormID> previousCell = 0x0;

	struct PluginForm
	{
		std::string_view name;
		void** formPtr;
		uint32_t formID;
		std::string_view pluginName;
		bool optional = false;
	};

	// Properties storing game form references
	inline RE::BGSKeyword* ActorTypeGhost;
	inline RE::TESSound* DeathEventSound_Subtle;
	inline RE::TESSound* DeathEventSound_DF;
	inline RE::TESImageSpaceModifier* DeathEventIMOD_Classic;
	inline RE::TESImageSpaceModifier* DeathEventIMOD_Mono;
	inline RE::TESImageSpaceModifier* DeathEventIMOD_Negative;

	static inline const std::vector<PluginForm> pluginForms = {
		{ "ActorTypeGhost", reinterpret_cast<void**>(&ActorTypeGhost), 0xD205E, "Skyrim.esm", true },
		{ "DeathEventSound_Subtle", reinterpret_cast<void**>(&DeathEventSound_Subtle), 0x80C, PLUGIN_NAME },
		{ "DeathEventSound_DF", reinterpret_cast<void**>(&DeathEventSound_DF), 0x80B, PLUGIN_NAME },
		{ "DeathEventIMOD_Classic", reinterpret_cast<void**>(&DeathEventIMOD_Classic), 0x801, PLUGIN_NAME },
		{ "DeathEventIMOD_Mono", reinterpret_cast<void**>(&DeathEventIMOD_Mono), 0x803, PLUGIN_NAME },
		{ "DeathEventIMOD_Negative", reinterpret_cast<void**>(&DeathEventIMOD_Negative), 0x802, PLUGIN_NAME }
	};

	inline RE::TESDataHandler* TESdataHandler;

	inline CIF_API::Interface* CIF_API_Interface = nullptr;
	inline DBF_API::Interface* DBF_API_Interface = nullptr;
	inline NGDecapitationsAPI::NGDecapitationsAPI* NGD_API_Interface = nullptr;
}
