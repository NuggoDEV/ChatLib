#include "iostream"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "scotland2/shared/modloader.h"
#include "beatsaber-hook/shared/utils/logging.hpp"


namespace ChatLib::CusLogger {

    class Log {
    public:
        std::string log;
        std::string type;
    };

    Logger* logger;
    std::vector<Log> logs;
    std::vector<void (*)(Log)> callbacks;

    std::vector<Log> getLogs () {
        return logs;
    }

    void out_info (std::string text) {
        logger->info("%s", text.c_str());

        Log log;
        log.log = text;
        log.type = "info";
        logs.push_back(log);

        for (int i = 0; i < callbacks.size(); i++) {
            callbacks[i](log);
        }
    }

    void out_severe (std::string error) {
        logger->error("%s", error.c_str());

        Log log;
        log.log = error;
        log.type = "error";
        logs.push_back(log);

        for (int i = 0; i < callbacks.size(); i++) {
            callbacks[i](log);
        }
    }

    void setup (modloader::ModInfo modInfo) {
        logger = new Logger(modInfo);
    }

    void registerCallback (void (*callback)(Log)) {
        callbacks.push_back(callback);
    }
}