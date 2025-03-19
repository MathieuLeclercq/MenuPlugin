#include "pch.h"
#include "MenuPlugin.h"


BAKKESMOD_PLUGIN(MenuPlugin, "go straight to menu from command line", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void MenuPlugin::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->registerNotifier("load_menu", [&](...) { ExitGame(); }, "", 0);
	//ExitGame();
}

void MenuPlugin::onUnload()
{
	LOG("MenuPlugin unloaded.");
}


void MenuPlugin::ExitGame()
{
	auto game = gameWrapper->GetOnlineGame();
	if (!game.IsNull())
	{
		if (!game.GetbMatchEnded())
		{
			LOG("Cannot exit game, match is not over.");
			return;
		}
	}
	LOG("Loading main menu...");
	cvarManager->executeCommand("unreal_command disconnect");
}
