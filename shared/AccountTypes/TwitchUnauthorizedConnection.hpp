#pragma once

#include <iostream>
#include <vector>
#include "IRC/TwitchIRCClient.hpp"
#include "Types/Twitch/Message.hpp"


namespace ChatLib::Types {

    class TwitchUnauthorizedConnection {
    public:
        std::string accountName;
        std::string channelName;

        TwitchUnauthorizedConnection(std::string accountName, std::string channelName);

        void registerMessageCallback(void (*callback)(ChatLib::Types::Twitch::Message));
        void terminate();


    private:
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<void (*)(ChatLib::Types::Twitch::Message)> messageCallbacks;
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };
}