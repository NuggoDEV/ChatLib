#include "Handler.hpp"

using namespace ChatLib::CusLogger;

namespace ChatLib::Handler {

    void initialize() {
        out_info("Hello from ChatLib init");
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