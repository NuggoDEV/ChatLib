#include "ChatLib.hpp"
#include "Logger.hpp"
#include "IRC/TestClient.hpp"

bool didInit = false;

Logger& getLogger()
{
    static auto logger = new Logger(ModInfo{"ChatLib", "0.0.1"}, LoggerOptions(false, true));
    return *logger;
}

extern "C" void setup(ModInfo& info)
{
    info.id = "ChatLib";
    info.version = "0.0.1";
}

extern "C" void load()
{
    ChatLib::Init();
    Test();
}

void ChatLib::Init()
{
    if (didInit)
        return;

    didInit = true;
    getLogger().info("Started initializing");

    il2cpp_functions::Init();
}