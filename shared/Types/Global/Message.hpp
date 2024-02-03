#pragma once

#include <string>

namespace ChatLib::Types::Global {

    /**
     * @brief Represents a Global chat message (all Platforms) with username and content.
     */
    struct Message {
        std::string username; /**< The username associated with the message. */
        std::string message;  /**< The content of the Twitch chat message. */
    };

}  // namespace ChatLib::Types::Global
