#include "AccountTypes/TwitchAccount.hpp"
#include <thread>
#include "libcurl/shared/curl.h"
#include "Logger.hpp"
#include "Helpers/TwitchTokenValidation.hpp"

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;

namespace ChatLib::Types {

    TwitchAuthorizedConnection::TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName)
            : accountName(accountName), token(token), channelName(channelName), connectionThread(nullptr) {

        this->connectionThread = new std::thread([this]() {
            bool tokenValid = validateToken(this->token, this->accountName);

            if (!tokenValid) {
                out_severe("Twitch token validation failed. Terminating connection.");
                return;
            }

            out_info("Twitch token validation successful. Starting connection.");
        });
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
