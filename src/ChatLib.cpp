#include "ChatLib.hpp"
#include "Logger.hpp"

using namespace ChatLib::CusLogger;

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

extern "C" void setup(CModInfo& info) {
    info.id = modInfo.id.c_str();
    info.version = modInfo.version.c_str();
    info.version_long = modInfo.versionLong;

    Logger::setup(modInfo);

    out_info("Loaded ChatLib!")
}
extern "C" void load() {
    il2cpp_functions::Init();

    out_info("Loaded ChatLib!")
}