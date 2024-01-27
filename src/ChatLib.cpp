#include "ChatLib.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(CModInfo& info) {
    info.id = modInfo.id.c_str();
    info.version = modInfo.version.c_str();
    info.version_long = modInfo.versionLong;

    getConfig().Load();
    getLogger().info("Completed setup!");
}
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    getLogger().info("Installed all hooks!");
}