#pragma once

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"

namespace ChatLib::Types {

    /**
     * @brief Represents an authorized connection to Twitch for sending and receiving messages.
     */
    class TwitchAuthorizedConnection {
    public:
        /**
         * @brief Constructor for TwitchAuthorizedConnection.
         * @param accountName The Twitch account name.
         * @param token The authorization token for the Twitch connection.
         * @param channelName The name of the Twitch channel.
         */
        TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName);

        /**
         * @brief Sends a message to the connected Twitch channel.
         * @param message The message to be sent.
         */
        void sendMessage(const std::string& message);

        /**
         * @brief Registers a callback function to handle incoming Twitch messages.
         * @param callback The callback function to be registered.
         */
        void registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message));

        /**
         * @brief Terminates the Twitch connection and stops message processing.
         */
        void terminate();


        std::string accountName;
        std::string channelName;

    private:
        std::string token;
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<std::string> messageQueue;
        std::vector<IRCMessage> newMessages;
        std::vector<void (*)(ChatLib::Types::Twitch::Message)> messageCallbacks;

        /**
         * @brief Callback function invoked on receiving an IRC message.
         * @param message The IRC message received.
         * @param client The Twitch IRC client handling the connection.
         */
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };
}  // namespace ChatLib::Types
