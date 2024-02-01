#include "libcurl/shared/curl.h"
#include <iostream>

namespace ChatLib::Helpers::TwitchTokenValidator {
    bool validateToken(std::string token, std::string accountName);
}