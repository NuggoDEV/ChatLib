#include "iostream"

namespace ChatLib::Internal::Accounts {
    struct AuthorizedTwitchConnection {
        std::string username;
        std::string safeStorageKey;
    };

    struct UnauthorizedTwitchConnection {
        std::string username;
    };
}