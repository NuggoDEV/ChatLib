#pragma once

#include <iostream>
#include <vector>
#include "IRC/TwitchIRCClient.hpp"


namespace ChatLib::Types {
    class TwitchAuthorizedConnection {
    public:
        std::vector<void (*)(std::string)> messageCallbacks;

        std::string accountName;
        std::string channelName;

        TwitchAuthorizedConnection(std::string accountName, std::string token, std::string channelName);

        void sendMessage(std::string message);
        void registerMessageCallback(void (*callback)(std::string));
        void getUserInfo(std::string username);
        void terminate();


    private:
        std::string token;
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<std::string> messageQueue;
        std::vector<IRCMessage> newMessages;
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };


    class TwitchUnauthorizedConnection {
    public:
        std::vector<void (*)(std::string)> messageCallbacks;

        std::string accountName;
        std::string channelName;

        TwitchUnauthorizedConnection(std::string accountName, std::string channelName);

        void registerMessageCallback(void (*callback)(std::string));
        void terminate();


    private:
        std::thread* connectionThread;
        std::atomic<bool> connectionTerminated = false;
        std::atomic<bool> connectionStarted = false;
        std::vector<IRCMessage> newMessages;
        void onIRCMessage(IRCMessage message, TwitchIRCClient* client);
    };
}