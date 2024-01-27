#include <utility>
#include <iostream>
#include <vector>
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "scotland2/shared/modloader.h"

namespace ChatLib::CusLogger {

    class Log {
    public:
        std::string log;
        std::string type;
    };

    Logger* logger = nullptr;
    std::vector<Log> logs;
    std::vector<void (*)(Log)> callbacks;

    const std::vector<Log>& getLogs() {
        return logs;
    }

    void out_info(const std::string& text) {
        if (logger) {
            logger->info("%s", text.c_str());
        }

        Log log{ text, "info" };
        logs.push_back(log);

        for (const auto& callback : callbacks) {
            callback(log);
        }
    }

    void out_severe(const std::string& error) {
        if (logger) {
            logger->error("%s", error.c_str());
        }

        Log log{ error, "error" };
        logs.push_back(log);

        for (const auto& callback : callbacks) {
            callback(log);
        }
    }

    void setup(modloader::ModInfo modInfo) {
        if (!logger) {
            logger = new Logger(std::move(modInfo));
        }
    }

    void registerCallback(void (*callback)(Log)) {
        callbacks.push_back(callback);
    }
}
