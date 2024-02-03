#pragma once

#include <string>

namespace ChatLib::Types::Twitch {

    /**
     * @brief Represents a Twitch chat message with username and content.
     */
    struct Message {
        std::string username; /**< The username associated with the message. */
        std::string message;  /**< The content of the Twitch chat message. */
    };

}  // namespace ChatLib::Types::Twitch
