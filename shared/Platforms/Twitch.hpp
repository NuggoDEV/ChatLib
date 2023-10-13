#pragma once

#include <string>
#include <vector>

#include "Objects/Twitch/Message.hpp"
#include "Objects/Twitch/User.hpp"
#include "Objects/Twitch/Client.hpp"

namespace Twitch::Connection {
    ///@brief Get information about the client
    ///@return Twitch::Client
    void getClient();
}