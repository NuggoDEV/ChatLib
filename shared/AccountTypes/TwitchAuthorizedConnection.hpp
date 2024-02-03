#pragma once

#include <iostream>
#include <vector>
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"


namespace ChatLib::Types {
    class TwitchAuthorizedConnection {
    public:
        std::string accountName;
        std::string channelName;

        TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName);

        void sendMessage(const std::string& message);
        void registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message));
        void terminate();


    private:
        std::string token;
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<std::string> messageQueue;
        std::vector<IRCMessage> newMessages;
        std::vector<void (*)(ChatLib::Types::Twitch::Message)> messageCallbacks;
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };
}