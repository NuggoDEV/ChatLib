#include "Handler.hpp"

#include "safestorage/shared/interface.hpp"

using namespace ChatLib::CusLogger;
using namespace ChatLib::Types;
using namespace SafeStorage::Interface;

namespace ChatLib::Handler {

    void initialize(CModInfo modInfo) {
        out_info("Hello from ChatLib init");

        for (auto connection : authorizedTwitchConnections) {
            if (!connection.isActivated) {
                continue;
            }
            out_info("Connecting Twitch Account: " + connection.username);

            SafePtrUnity<TwitchAuthorizedConnection> twitchConnection = new TwitchAuthorizedConnection(connection.username, get(modInfo.id, connection.safeStorageKey), connection.listeningChannel);
            activeAuthorizedTwitchConnections.push_back(twitchConnection);
        }

        for (auto connection : unauthorizedTwitchConnections) {
            if (!connection.isActivated) {
                continue;
            }
            out_info("Connecting Twitch Account: " + connection.username);

            SafePtrUnity<TwitchUnauthorizedConnection> twitchConnection = new TwitchUnauthorizedConnection(connection.username, connection.listeningChannel);
            activeUnauthorizedTwitchConnections.push_back(twitchConnection);
        }
    }

    void addGlobalCallback(std::function<void(ChatLib::Types::Global::Message)> callback) {
        globalCallbacks.push_back(callback);
    }

    void handleGlobalMessage(ChatLib::Types::Global::Message message) {
        for (auto callback : globalCallbacks) {
            callback(message);
        }
    }

}