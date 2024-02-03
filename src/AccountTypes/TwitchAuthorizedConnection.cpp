#include "AccountTypes/TwitchAuthorizedConnection.hpp"
#include <thread>
#include <utility>
#include "Logger.hpp"
#include "Helpers/TwitchTokenValidation.hpp"
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;
using namespace ChatLib::Types::Twitch;

namespace ChatLib::Types {

    TwitchAuthorizedConnection::TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName)
            : accountName(std::move(accountName)), token(std::move(token)), channelName(std::move(channelName)), connectionThread(nullptr) {

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

            client.HookIRCCommand("PRIVMSG", [this](IRCMessage message, TwitchIRCClient* client) {
                this->onIRCMessage(std::move(message), client);
            });

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

    void TwitchAuthorizedConnection::sendMessage(const std::string& message) {
        this->messageQueue.push_back(message);
    }

    void TwitchAuthorizedConnection::registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchAuthorizedConnection::terminate() {
        this->connectionTerminated = true;
    }

    // this method is private and only called from the connection thread
    void TwitchAuthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
        Message msg = Message();
        msg.message = message.parameters[1];
        msg.username = message.prefix.nick;
        for (auto &callback : messageCallbacks) {
            callback(msg);
        }
    }
}
