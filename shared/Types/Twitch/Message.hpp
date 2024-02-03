#pragma once

#include <string>

namespace ChatLib::Types::Twitch {
    struct Message {
        std::string username;
        std::string message;
    };
}