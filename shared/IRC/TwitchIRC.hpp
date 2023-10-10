#pragma once

#include "Objects/Message.hpp"

namespace TwitchIRC {
    class BotConnection {
    private:
        std::string username = nullptr;
        std::string token = nullptr;
        std::string channel = nullptr;
        bool connected = false;

    public:
        ///@brief Connect as a user (Client) to a twitch channel
        ///@tparam username Name of the Client
        ///@tparam token Auth Token of the Client
        ///@tparam channel Name of the Channel to listen to
        void connect(std::string username, std::string token, std::string channel); // Connects / Reconnects with the given account to the given channel
        ///@brief Disconnects the Client
        void disconnect();
        ///@brief Get information about the client
        void getUser();
    };

    class MessageListener {
    private:
        std::vector<std::function<void(Twitch::Message* message)>> OnMessageEvents;
        std::string channel = nullptr;
        bool connected = false;

    public:
        ///@brief Connect to a channel to listen to messages
        ///@tparam channel Name of the Channel
        void connect(std::string channel);
        ///@brief Register a message Callback
        ///@tparam onMessage Callback function
        void registerMessageCallback(std::function<void(Twitch::Message* message)> const& onMessage);
    };
}