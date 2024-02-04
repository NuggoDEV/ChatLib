#pragma once

#include <string>

namespace ChatLib::Types::Global {

    /**
     * @brief Represents a Platform for a chat message.
     */
    enum class Platform {
        Twitch, /**< The message is from Twitch. */
    };

    /**
     * @brief Represents a Global chat message (all Platforms) with username and content.
     */
    struct Message {
        std::string username; /**< The username associated with the message. */
        std::string message;  /**< The content of the Twitch chat message. */
        ChatLib::Types::Global::Platform platform; /**< The platform the message is from. */
    };

}  // namespace ChatLib::Types::Global
