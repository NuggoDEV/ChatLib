#include "AccountTypes/TwitchAccount.hpp"
#include <thread>

namespace ChatLib::Types {

    TwitchAuthorizedConnection::TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName)
            : accountName(accountName), token(token), channelName(channelName), connectionThread(nullptr) {
    }

    void TwitchAuthorizedConnection::sendMessage(std::string message) {
    }

    void TwitchAuthorizedConnection::registerMessageCallback(void (*callback)(std::string)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchAuthorizedConnection::getUserInfo(std::string username) {
    }

    void TwitchAuthorizedConnection::terminate() {
    }


    // TwitchUnauthorizedConnection Implementierung
    TwitchUnauthorizedConnection::TwitchUnauthorizedConnection(std::string accountName, std::string channelName)
            : accountName(accountName), channelName(channelName), connectionThread(nullptr) {}

    void TwitchUnauthorizedConnection::registerMessageCallback(void (*callback)(std::string)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchUnauthorizedConnection::terminate() {
    }

}
