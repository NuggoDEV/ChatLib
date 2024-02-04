#include "iostream"

namespace ChatLib::Internal::Accounts {
    struct AuthorizedTwitchConnection {
        std::string username;
        std::string safeStorageKey;
        bool isActivated;
    };

    struct UnauthorizedTwitchConnection {
        std::string username;
        bool isActivated;
    };
}