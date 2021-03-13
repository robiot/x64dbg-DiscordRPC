#include "plugin.h"
#include <Windows.h>

#define MAX_SCAN_SIZE 0x1000

#include <chrono>//.
#include "DiscordSDK/include/discord_rpc.h"
#include "DiscordSDK/include/discord_register.h"

static bool gInit, gRPC = true;

void _plugin_registercallback(
	int pluginHandle, //plugin handle
	CBTYPE cbType, //event type
	CBPLUGIN cbPlugin //callback function
);

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

static void UpdateDiscord(const char *_state)
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::string almost_real_state = "Debugging ";
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

static duint cbStackContains(int argc, duint* argv, void* userdata)
{
    // Make sure the right amount of arguments was supplied
    if (argc < 2)
        return 0;

    // Get the 'csp' (address to start scanning from).
    auto csp = argv[0];
    duint size;
    auto base = DbgMemFindBaseAddr(csp, &size);

    // Make sure that the supplied address is in a valid memory range
    if (!base)
        return 0;

    // Read MAX_SCAN_SIZE bytes from the stack to scan
    duint data[MAX_SCAN_SIZE / sizeof(duint)];
    auto sizeLeft = size - (csp - base);
    auto readSize = sizeLeft >= sizeof(data) ? sizeof(data) : sizeLeft;
    DbgMemRead(csp, data, readSize);

    // Scan the bytes to see if it contains the requested value
    for (duint i = 0; i * sizeof(duint) < readSize; i++)
        if (data[i] == argv[1])
            return true;
    return false;
}

//Initialize plugin data
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if (!_plugin_registerexprfunction(pluginHandle, "stack.contains", 2, cbStackContains, nullptr))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the stack.contains expression function!");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize plugin data (clearing menus optional).
bool pluginStop()
{
    return true;
}

//Start
void pluginSetup()
{
	SetupDiscord();
	UpdateDiscord("niceCOCK.exe");
}
