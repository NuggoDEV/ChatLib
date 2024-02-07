#include "iostream"

namespace ChatLib::Internal::Accounts {
    struct AuthorizedTwitchConnection {
        std::string username;
        std::string safeStorageKey;
        std::string listeningChannel;
        bool isActivated;
    };

    struct UnauthorizedTwitchConnection {
        std::string username;
        std::string listeningChannel;
        bool isActivated;
    };
}