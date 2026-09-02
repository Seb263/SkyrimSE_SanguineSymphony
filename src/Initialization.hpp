#pragma once

#include "DataHandler.hpp"
#include "Events.h"
#include "Hooks.hpp"
#include "SettingsIni.hpp"

#include "Core/Structure.h"
#include "Core/Main.hpp"

#include "Utils/MiscUtils.hpp"
#include "Utils/ModUtils.hpp"
#include "Utils/TimeUtils.hpp"

#include "API/CIF-API.h"
#include "API/DBF-API.h"
#include "API/NGD-API.h"

namespace ModData
{
	class DataHandler
	{
	public:
		bool preLoaded = false;
		bool postLoaded = false;
		bool postLoadedAlternate = false;

		static DataHandler* GetSingleton()
		{
			static DataHandler singleton;
			return &singleton;
		}

		void PreLoadData()
		{
			if (preLoaded) return;
			preLoaded = true;

			TESdataHandler = RE::TESDataHandler::GetSingleton();

			LoadPluginsForms();
			SettingsIni::SettingsManager::GetSingleton().SyncToGlobals();
			ModUtils::ApplyRuntimeSettings();

			Events::Hooks::InstallHooks();
			Events::ModEventSink::LoadEvents();
		}

		void PostLoadData()
		{
			if (postLoaded) return;
			postLoaded = true;

			if (!LoadCIFApi()) return;

			if (auto* apiInterface = static_cast<DBF_API::Interface*>(DBF_API::GetAPI())) {
				DBF_API_Interface = apiInterface;
				logger::info("Dynamic Bloodpool Framework API v{} registered successfully.", apiInterface->GetVersion().string("."));
			} else {
				logger::warn("Dynamic Bloodpool Framework API not found.");
			}

			if (NGDecapitationsAPI::LoadAPI()) {
				NGD_API_Interface = NGDecapitationsAPI::g_API;
				const auto version = NGD_API_Interface->GetVersion();

				const auto major = (version >> 16) & 0xFF;
				const auto minor = (version >> 8) & 0xFF;
				const auto patch = version & 0xFF;

				logger::info("Next-Gen Decapitations API v{}.{}.{}.0 registered successfully.", major, minor, patch);
			}
		}

		void PostLoadDataAlternate()
		{
			if (postLoadedAlternate) return;
			postLoadedAlternate = true;

			TimeUtils::DoWhile(100ms, [](TimeUtils::CallResult result, std::chrono::nanoseconds) {
				if (TimeUtils::IsEnd(result)) return true;

				auto player = RE::PlayerCharacter::GetSingleton();
				if (player && player->Is3DLoaded() && player->GetParentCell() && player->GetParentCell()->IsAttached()) {
					GetSingleton()->PostLoadData();
					return false;
				}

				return true;
			}, true);
		}

	private:
		static inline void LoadPluginsForms()
		{
			logger::info("Loading Plugins Froms Data...");

			for (const auto& formInfo : pluginForms) {
				*formInfo.formPtr = TESdataHandler->LookupForm(formInfo.formID, formInfo.pluginName.data());
				if (!*formInfo.formPtr && !formInfo.optional) {
					if (formInfo.pluginName == PLUGIN_NAME) {
						REPORT_AND_FAIL(
							"ERROR: The required plugin \"{}\" is missing! This means the mod is either not installed correctly or your mod manager failed to enable it.\n"
							"If you believe you installed the mod properly, please redo the manual installation without using a mod manager.\n\n"
							"This is NOT a bug - DO NOT report it! Instructions for manual installation are available on the mod's page.\n\n"
							"DETAILS: Form \"{}\" not found in \"{}\".",
							formInfo.pluginName, formInfo.name, formInfo.pluginName);
					} else {
						REPORT_AND_FAIL("ERROR: Form \"{}\" not found in \"{}\".", formInfo.name, formInfo.pluginName);
					}
				}
			}

			logger::info("Loading Plugins Froms Data: DONE");
		}

		static inline bool LoadCIFApi()
		{
			constexpr REL::Version kRequiredVersion{ 2, 0, 0, 0 };
			const auto dllVersion = MiscUtils::GetPluginVersion("CoreImpactFramework.dll");
			const bool versionOk = dllVersion != REL::Version{} && dllVersion >= kRequiredVersion;

			auto* apiInterface = versionOk ? static_cast<CIF_API::Interface*>(CIF_API::GetAPI()) : nullptr;

			if (!apiInterface) {
				logger::error("Core Impact Framework API not found or version insufficient.");

				const std::string title = fmt::format("{}: Missing Requirement", MOD_NAME);
				const std::string msg_box = fmt::format(
					"The Core Impact Framework version {} or higher is required to run {}.\n\n"
					"Would you like to close the game and open the download page?",
					kRequiredVersion.string("."), MOD_NAME);

				if (REX::W32::MessageBoxA(nullptr, msg_box.c_str(), title.c_str(), MB_ICONWARNING | MB_YESNO) == IDYES) {
					::ShellExecuteA(nullptr, "open", "https://www.seb263.fr/short-url/cif-v2", nullptr, nullptr, SW_SHOWNORMAL);
					REX::W32::TerminateProcess(REX::W32::GetCurrentProcess(), EXIT_FAILURE);
				}
				return false;
			}

			CIF_API_Interface = apiInterface;
			logger::info("Core Impact Framework API v{} registered successfully.", apiInterface->GetVersion().string("."));

			CIF_API_Interface->RegisterPostDeferredHitCallback((std::string)MOD_NAME, 20, [](const std::string& eventName, CIF_API::Interface::RuntimeHitContext context) {
				ModCore::Main::ProcessDeferredHit(static_cast<CoreStructure::RuntimeHitContext>(context));
			});
			return true;
		}
	};
}
