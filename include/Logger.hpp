#include <utility>
#include <iostream>
#include <vector>
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "scotland2/shared/modloader.h"

namespace ChatLib::CusLogger {

    class Log {
    public:
        std::string log; /**< The log message content. */
        std::string type; /**< The type of log message (e.g., "info", "error"). */
    };

    Logger* logger = nullptr; /**< Pointer to the logger instance. */
    std::vector<Log> logs; /**< Vector to store logged messages. */
    std::vector<void (*)(Log)> callbacks; /**< Vector to store log callback functions. */

    /**
     * @brief Gets the vector of logged messages.
     * @return The vector of logged messages.
     */
    const std::vector<Log>& getLogs() {
        return logs;
    }

    /**
     * @brief Logs an informational message.
     * @param text The informational message text.
     */
    void out_info(const std::string& text) {
        if (logger) {
            logger->info("%s", text.c_str());
        }

        Log log{ text, "info" };
        logs.push_back(log);

        // Notify registered callbacks
        for (const auto& callback : callbacks) {
            callback(log);
        }
    }

    /**
     * @brief Logs a severe (error) message.
     * @param error The error message text.
     */
    void out_severe(const std::string& error) {
        if (logger) {
            logger->error("%s", error.c_str());
        }

        Log log{ error, "error" };
        logs.push_back(log);

        // Notify registered callbacks
        for (const auto& callback : callbacks) {
            callback(log);
        }
    }

    /**
     * @brief Initializes the logger with mod information.
     * @param modInfo The mod information required for logger setup.
     */
    void setup(modloader::ModInfo modInfo) {
        if (!logger) {
            logger = new Logger(std::move(modInfo));
        }
    }

    /**
     * @brief Registers a callback function to handle log messages.
     * @param callback The callback function to be registered.
     */
    void registerCallback(void (*callback)(Log)) {
        callbacks.push_back(callback);
    }
}
