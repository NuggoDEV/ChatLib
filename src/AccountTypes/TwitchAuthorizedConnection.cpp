#include "AccountTypes/TwitchAuthorizedConnection.hpp"
#include <utility>
#include <thread>
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

        // Connection thread for handling Twitch IRC communication
        this->connectionThread = new std::thread([this]() {
            // Validate token and check for termination before starting the connection
            if (!validateToken(this->token, this->accountName) || this->connectionTerminated || this->connectionStarted) {
                return;
            }
            this->connectionStarted = true;

            TwitchIRCClient client = TwitchIRCClient();

            // Initialize and connect to Twitch IRC
            client.InitSocket();
            client.Connect();
            client.Login(this->accountName, this->token);
            client.JoinChannel(this->channelName);

            // Hook IRC command to handle PRIVMSG (incoming messages)
            client.HookIRCCommand("PRIVMSG", [this](IRCMessage message, TwitchIRCClient* client) {
                this->onIRCMessage(std::move(message), client);
            });

            // Main loop for handling messages and termination
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
        // Queue a message to be sent to the Twitch channel
        this->messageQueue.push_back(message);
    }

    void TwitchAuthorizedConnection::registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message)) {
        // Register a callback function to handle incoming Twitch messages
        messageCallbacks.push_back(callback);
    }

    void TwitchAuthorizedConnection::terminate() {
        // Set the connection termination flag
        this->connectionTerminated = true;
    }

    // Private method called from the connection thread to handle incoming IRC messages
    void TwitchAuthorizedConnection::onIRCMessage(IRCMessage message, TwitchIRCClient* client) {
        // Extract relevant information from IRC message and invoke registered callbacks
        Message msg = Message();
        msg.message = message.parameters[1];
        msg.username = message.prefix.nick;
        for (auto &callback : messageCallbacks) {
            callback(msg);
        }
    }

}  // namespace ChatLib::Types
