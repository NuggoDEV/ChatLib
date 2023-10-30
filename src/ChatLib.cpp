#include "ChatLib.hpp"
#include "Logger.hpp"
#include "WebServer/WebServer.hpp"
#include "UI/CLView.hpp"
#include "bsml/shared/BSML.hpp"

bool didInit = false;

Logger& getLogger()
{
    static auto logger = new Logger(ModInfo{MOD_ID, VERSION}, LoggerOptions(false, true));
    return *logger;
}

extern "C" void setup(ModInfo& info)
{
    info.id = MOD_ID;
    info.version = VERSION;
}

extern "C" void load()
{
    ChatLib::Init();
}

void ChatLib::Init()
{
    if (didInit)
        return;
    didInit = true;
    il2cpp_functions::Init();

    getLogger().info("Started initializing");
    WebServer::start();
    BSML::Register::RegisterSettingsMenu<ChatLib::UI::CLView*>("ChatLib", false);
} 