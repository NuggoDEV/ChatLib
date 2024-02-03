#include "AccountTypes/TwitchUnauthorizedConnection.hpp"
#include <thread>
#include "Logger.hpp"
#include "Helpers/TwitchTokenValidation.hpp"
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;
using namespace ChatLib::Types::Twitch;

namespace ChatLib::Types {

    TwitchUnauthorizedConnection::TwitchUnauthorizedConnection(std::string accountName, std::string channelName)
            : accountName(accountName), channelName(channelName), connectionThread(nullptr) {

        if (this->connectionStarted) return;

        this->connectionThread = new std::thread([this]() {
            if(this->connectionTerminated) return;
            if (this->connectionStarted) return;
            this->connectionStarted = true;

            TwitchIRCClient client = TwitchIRCClient();

            client.InitSocket();
            client.Connect();
            client.JoinChannel(this->channelName);

            client.HookIRCCommand("PRIVMSG", [this](IRCMessage message, TwitchIRCClient* client) {
                this->onIRCMessage(std::move(message), client);
            });

            while (true) {
                if (this->connectionTerminated) {
                    client.Disconnect();
                    break;
                }
            }
        });
    }

    void TwitchUnauthorizedConnection::registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message)) {
        messageCallbacks.push_back(callback);
    }

    void TwitchUnauthorizedConnection::terminate() {
        this->connectionTerminated = true;
    }

    void TwitchUnauthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
        Message msg = Message();
        msg.message = message.parameters[1];
        msg.username = message.prefix.nick;
        for (auto &callback : messageCallbacks) {
            callback(msg);
        }
    }
}
