#pragma once

#include "AccountTypes/TwitchAuthorizedConnection.hpp"
#include "AccountTypes/TwitchUnauthorizedConnection.hpp"

#include "iostream"

namespace ChatLib {
    std::vector<ChatLib::Types::TwitchAuthorizedConnection> getAuthorizedTwitchConnections;
    std::vector<ChatLib::Types::TwitchUnauthorizedConnection> getUnauthorizedTwitchConnections;
}