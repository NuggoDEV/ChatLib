#include "ChatLib.hpp"
#include "Logger.hpp"
#include "Internal/AccountStorage.hpp"
#include "safestorage/shared/interface.hpp"
#include "Helpers/TwitchTokenValidation.hpp"
#include "Handler.hpp"

using namespace ChatLib::CusLogger;

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

void validateConfig() {
    std::vector<ChatLib::Internal::Accounts::AuthorizedTwitchConnection> invalidAuthorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::AuthorizedTwitchConnection> authorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::UnauthorizedTwitchConnection> invalidUnauthorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::UnauthorizedTwitchConnection> unauthorizedTwitchConnections;

    // check if there is a vector for ChatLib::Internal::Accounts::AuthorizedTwitchConnection in the config
    if (!getConfig().config.HasMember("AuthorizedTwitchConnections") || !getConfig().config["AuthorizedTwitchConnections"].IsArray()) {
        getConfig().config.AddMember("AuthorizedTwitchConnections", rapidjson::Value(rapidjson::kArrayType), getConfig().config.GetAllocator());
        getConfig().Write();
    } else {
        // for every entry, validiate that it has a username and safeStorageKey
        for (auto& entry : getConfig().config["AuthorizedTwitchConnections"].GetArray()) {
            ChatLib::Internal::Accounts::AuthorizedTwitchConnection connection;
            connection.username = entry["username"].GetString();
            connection.safeStorageKey = entry["safeStorageKey"].GetString();
            connection.isActivated = entry["isActivated"].GetBool();

            // check if all the values are present
            if (connection.username.empty() || connection.safeStorageKey.empty()) {
                invalidAuthorizedTwitchConnections.push_back(connection);
                // remove the entry from the config
                getConfig().config["AuthorizedTwitchConnections"].Erase(&entry);
                out_severe("Invalid Authorized Twitch Connection found");
                continue;
            }

            // check if safeStorage has the key
            if (SafeStorage::Interface::get(modInfo.id, connection.safeStorageKey).empty()) {
                invalidAuthorizedTwitchConnections.push_back(connection);
                // remove the entry from the config
                getConfig().config["AuthorizedTwitchConnections"].Erase(&entry);
                out_severe("Invalid SafeStorage Key found");
            } else {
                // check if the token is valid
                if (!ChatLib::Helpers::TwitchTokenValidator::validateToken(SafeStorage::Interface::get(modInfo.id, connection.safeStorageKey), connection.username)) {
                    invalidAuthorizedTwitchConnections.push_back(connection);
                    // remove the token from safeStorage
                    SafeStorage::Interface::remove(modInfo.id, connection.safeStorageKey);
                    // remove the entry from the config
                    getConfig().config["AuthorizedTwitchConnections"].Erase(&entry);
                    out_severe("Invalid Twitch Token found");
                } else {
                    authorizedTwitchConnections.push_back(connection);
                    out_info("Valid Twitch Token found");
                }
            }
        }
    }

    // check if there is a vector for ChatLib::Internal::Accounts::UnauthorizedTwitchConnection in the config
    if (!getConfig().config.HasMember("UnauthorizedTwitchConnections") || !getConfig().config["UnauthorizedTwitchConnections"].IsArray()) {
        getConfig().config.AddMember("UnauthorizedTwitchConnections", rapidjson::Value(rapidjson::kArrayType), getConfig().config.GetAllocator());
        getConfig().Write();
    }else {
        for (auto& entry : getConfig().config["UnauthorizedTwitchConnections"].GetArray()) {
            ChatLib::Internal::Accounts::UnauthorizedTwitchConnection connection;
            connection.username = entry["username"].GetString();
            connection.isActivated = entry["isActivated"].GetBool();

            if (connection.username.empty()) {
                invalidUnauthorizedTwitchConnections.push_back(connection);
                // remove the entry from the config
                getConfig().config["UnauthorizedTwitchConnections"].Erase(&entry);
                out_severe("Invalid Unauthorized Twitch Connection found");
                continue;
            }

            unauthorizedTwitchConnections.push_back(connection);
        }
    }


    ChatLib::Handler::invalidAuthorizedTwitchConnections = invalidAuthorizedTwitchConnections;
    ChatLib::Handler::authorizedTwitchConnections = authorizedTwitchConnections;
    ChatLib::Handler::invalidUnauthorizedTwitchConnections = invalidUnauthorizedTwitchConnections;
    ChatLib::Handler::unauthorizedTwitchConnections = unauthorizedTwitchConnections;
}

extern "C" void setup(CModInfo& info) {
    info.id = modInfo.id.c_str();
    info.version = modInfo.version.c_str();
    info.version_long = modInfo.versionLong;

    ChatLib::CusLogger::setup(modInfo);
    out_info("Loaded ChatLib!");

    getConfig().Load();
}
extern "C" void load() {
    il2cpp_functions::Init();

    validateConfig();

    ChatLib::Handler::initialize();

    out_info("Loaded ChatLib!");
}