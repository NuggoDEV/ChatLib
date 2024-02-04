#pragma once

#include <iostream>

#include "Types/Global/Message.hpp"
#include "Internal/AccountStorage.hpp"
#include "Logger.hpp"

namespace ChatLib::Handler {
    std::vector<ChatLib::Internal::Accounts::AuthorizedTwitchConnection> invalidAuthorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::AuthorizedTwitchConnection> authorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::UnauthorizedTwitchConnection> invalidUnauthorizedTwitchConnections;
    std::vector<ChatLib::Internal::Accounts::UnauthorizedTwitchConnection> unauthorizedTwitchConnections;

    std::vector<std::function<void(ChatLib::Types::Global::Message)>> globalCallbacks;

    void addGlobalCallback(std::function<void(ChatLib::Types::Global::Message)> callback);
    void handleGlobalMessage(ChatLib::Types::Global::Message message);
    void initialize();

}