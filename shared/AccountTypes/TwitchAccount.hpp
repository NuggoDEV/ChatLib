#pragma once

#include <iostream>
#include <vector>


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
    };
}