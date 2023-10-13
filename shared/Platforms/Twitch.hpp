#pragma once

#include <string>
#include <vector>
#include "Objects/Twitch/Message.hpp"

namespace Twitch::Connection {
    std::string username = nullptr;
    std::string token = nullptr;
    std::string channel = nullptr;
    bool connected = false;

    ///@brief Connect as a user (Client) to a twitch channel
    ///@tparam username Name of the Client
    ///@tparam token Auth Token of the Client
    ///@tparam channel Name of the Channel to listen to
    void connect(std::string username, std::string token, std::string channel); // Connects / Reconnects with the given account to the given channel
    ///@brief Disconnects the Client
    void disconnect();
    ///@brief Get information about the client
    void getUser();
}