#pragma once

#include <string>

namespace ChatLib::Models
{
    struct TwitchUser
    {
        std::string id;
        std::string username;
        std::string displayName;
        std::string description;
        std::string profileImage;
        std::string createdAt;
    };
}