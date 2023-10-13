#include <string>

namespace Twitch {

    class Username {
    private:

    public:
        std::string name = nullptr;
        bool isFollowing = false;
        bool isSubbed = false;
        bool isBanned = false;
        bool isTimeouted = false;

    };
}