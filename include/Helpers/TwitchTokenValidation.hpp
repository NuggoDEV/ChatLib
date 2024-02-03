#pragma once

#include "libcurl/shared/curl.h"
#include <iostream>

namespace ChatLib::Helpers::TwitchTokenValidator {

    /**
     * @brief Validates a Twitch token for a given account.
     * @param token The Twitch authentication token to be validated.
     * @param accountName The Twitch account name associated with the token.
     * @return True if the token is valid for the specified account, otherwise false.
     */
    bool validateToken(std::string token, std::string accountName);

}  // namespace ChatLib::Helpers::TwitchTokenValidator
