#include "AccountTypes/TwitchAccount.hpp"
#include <thread>
#include "Logger.hpp"
#include "Helpers/TwitchTokenValidation.hpp"
#include "IRC/TwitchIRCClient.hpp"

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;

namespace ChatLib::Types {

    TwitchAuthorizedConnection::TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName)
            : accountName(accountName), token(token), channelName(channelName), connectionThread(nullptr) {

        if (this->connectionStarted) return;

        this->connectionThread = new std::thread([this]() {
            if (!validateToken(this->token, this->accountName)) return;
            if(this->connectionTerminated) return;
            if (this->connectionStarted) return;
            this->connectionStarted = true;

            TwitchIRCClient client = TwitchIRCClient();

            client.InitSocket();
            client.Connect();
            client.Login(this->accountName, this->token);
            client.JoinChannel(this->channelName);

            


            while (true) {
                if (this->connectionTerminated) {
                    client.Disconnect();
                    break;
                }

                if (!this->messageQueue.empty()) {
                    std::string message = this->messageQueue[0];
                    this->messageQueue.erase(this->messageQueue.begin());
                    client.SendChatMessage(message);
                }
            }



        });
    }

    void TwitchAuthorizedConnection::sendMessage(std::string message) {
        this->messageQueue.push_back(message);
    }

    void TwitchAuthorizedConnection::registerMessageCallback(void (*callback)(std::string)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchAuthorizedConnection::getUserInfo(std::string username) {
    }

    void TwitchAuthorizedConnection::terminate() {
        this->connectionTerminated = true;
    }

    void TwitchAuthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
    }


    TwitchUnauthorizedConnection::TwitchUnauthorizedConnection(std::string accountName, std::string channelName)
            : accountName(accountName), channelName(channelName), connectionThread(nullptr) {

    }

    void TwitchUnauthorizedConnection::registerMessageCallback(void (*callback)(std::string)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchUnauthorizedConnection::terminate() {
        this->connectionTerminated = true;
    }

    void TwitchUnauthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
    }
}
