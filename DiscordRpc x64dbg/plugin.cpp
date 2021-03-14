#include "plugin.h"
#include <Windows.h>

#include <chrono>//.
#include "DiscordSDK/include/discord_rpc.h"
#include "DiscordSDK/include/discord_register.h"
#include <condition_variable>
#include <string>

static bool gInit, gRPC = true;
int ProcessId;

void SetupDiscord()
{
	if (gRPC)
	{
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize("820011598121926736", &handlers, 1, "0");
	}
	else
	{
		Discord_Shutdown();
	}
}

static void UpdateDiscord(const char * _dbging, const char *_state)
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::string almost_real_state = _dbging;
	almost_real_state += _state;
	const char* real_state = almost_real_state.c_str();


	if (gRPC)
	{
		static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = real_state;
		discordPresence.startTimestamp = StartTime;
		discordPresence.endTimestamp = NULL;
		discordPresence.largeImageKey = "x64dbg";
		discordPresence.largeImageText = "x64dbg";
		Discord_UpdatePresence(&discordPresence);

		Discord_UpdatePresence(&discordPresence);
	}
	else
	{
		Discord_ClearPresence();
	}
}

static void initDbg(CBTYPE cbType, void* callbackInfo) 
{
	//Get the filename, this maybe could have been done easier but it works
	PLUG_CB_INITDEBUG* i = (PLUG_CB_INITDEBUG*)callbackInfo;
	const char* filepath = i->szFileName;
	std::string filepath_modify(filepath);
	const size_t last_slash_idx = filepath_modify.rfind('\\', filepath_modify.length());
	if (std::string::npos != last_slash_idx)
	{
		filepath_modify = filepath_modify.substr(last_slash_idx + 1, filepath_modify.length() - last_slash_idx);
	};

	auto filename = filepath_modify.c_str();
    	UpdateDiscord("Debugging ", filename);
}

static void stopDbg(CBTYPE cbType, void* callbackInfo)
{
	UpdateDiscord("Idling", "");
}

//Initialize plugin data
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	//Initialize functions
    _plugin_registercallback(pluginHandle, CB_INITDEBUG, initDbg);
	_plugin_registercallback(pluginHandle, CB_STOPDEBUG, stopDbg);

    return true;
}

//Deinitialize plugin data
bool pluginStop()
{
    return true;
}

//Enable/Disable may be added in the future
/*enum MenuItems : int {
	MENU_DISABLE
};*/

//Start
void pluginSetup()
{
	SetupDiscord();
	UpdateDiscord("Idling","");
	_plugin_logprint("Discord Rpc Started\n");
	//_plugin_menuaddentry(hMenu, MENU_OPTIONS, "&Options");
	int hProfile = _plugin_menuadd(hMenu, "&Load Profile");

	/*_plugin_menuaddseparator(hMenu);
	_plugin_menuaddentry(hMenu, MENU_DISABLE, "&Disable RPC");*/
}
