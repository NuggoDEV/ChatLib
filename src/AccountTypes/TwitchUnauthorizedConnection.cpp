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

        // Connection thread for handling Twitch IRC communication
        this->connectionThread = new std::thread([this]() {
            // Check for termination and whether the connection has already started
            if (this->connectionTerminated || this->connectionStarted) {
                return;
            }
            this->connectionStarted = true;

            TwitchIRCClient client = TwitchIRCClient();

            // Initialize and connect to Twitch IRC
            client.InitSocket();
            client.Connect();
            client.JoinChannel(this->channelName);

            // Hook IRC command to handle PRIVMSG (incoming messages)
            client.HookIRCCommand("PRIVMSG", [this](IRCMessage message, TwitchIRCClient* client) {
                this->onIRCMessage(std::move(message), client);
            });

            // Main loop for handling termination
            while (true) {
                if (this->connectionTerminated) {
                    client.Disconnect();
                    break;
                }
            }
        });
    }

    void TwitchUnauthorizedConnection::registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message)) {
        // Register a callback function to handle incoming Twitch messages
        messageCallbacks.push_back(callback);
    }

    void TwitchUnauthorizedConnection::terminate() {
        // Set the connection termination flag
        this->connectionTerminated = true;
    }

    // Private method called from the connection thread to handle incoming IRC messages
    void TwitchUnauthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
        // Extract relevant information from IRC message and invoke registered callbacks
        Message msg = Message();
        msg.message = message.parameters[1];
        msg.username = message.prefix.nick;
        for (auto &callback : messageCallbacks) {
            callback(msg);
        }
    }

}  // namespace ChatLib::Types
