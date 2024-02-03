#pragma once

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"

namespace ChatLib::Types {

    /**
     * @brief Represents an unauthorized connection to Twitch for handling incoming messages.
     */
    class TwitchUnauthorizedConnection {
    public:
        /**
         * @brief Constructor for TwitchUnauthorizedConnection.
         * @param accountName The Twitch account name.
         * @param channelName The name of the Twitch channel.
         */
        TwitchUnauthorizedConnection(std::string accountName, std::string channelName);

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
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<void (*)(ChatLib::Types::Twitch::Message)> messageCallbacks;

        /**
         * @brief Callback function invoked on receiving an IRC message.
         * @param message The IRC message received.
         * @param client The Twitch IRC client handling the connection.
         */
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };
}  // namespace ChatLib::Types
