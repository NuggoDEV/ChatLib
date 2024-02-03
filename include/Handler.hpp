#pragma once

#include <iostream>

#include "Types/Global/Message.hpp"

namespace ChatLib::Handler {
    std::vector<std::function<void(ChatLib::Types::Global::Message)>> globalCallbacks;

    void addGlobalCallback(std::function<void(ChatLib::Types::Global::Message)> callback);

    void handleGlobalMessage(ChatLib::Types::Global::Message message);

}