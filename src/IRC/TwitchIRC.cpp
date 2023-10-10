#include "IRC/TwitchIRC.hpp"

namespace TwitchIRC {
    class BotConnection {
        void connect(std::string username, std::string token, std::string channel) {

        }
        void disconnect() {

        }
        void getUser() {

        }
    };

    class MessageListener {

        void connect(std::string channel) {
            // Connect to IRC
        }
        void registerMessageCallback(std::function<void(Twitch::Message* message)> const& onMessage) {
            this.OnMessageEvent->push_back(onMessage);
        }
    };
}