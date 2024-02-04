#include "Handler.hpp"

namespace ChatLib::Handler {

    void initialize() {
    }

    void addGlobalCallback(std::function<void(ChatLib::Types::Global::Message)> callback) {
        globalCallbacks.push_back(callback);
    }

    void handleGlobalMessage(ChatLib::Types::Global::Message message) {
        for (auto callback : globalCallbacks) {
            callback(message);
        }
    }

}