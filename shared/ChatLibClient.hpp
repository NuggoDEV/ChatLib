#pragma once

#include <string>

namespace ChatLib
{
    class ChatLibClient
    {
        public:
        void Connect(std::string channel);
        void Disconnect();
    };
}