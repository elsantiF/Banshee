#include "Logger.h"

namespace BansheeEngine {
    void Logger::InternalPrint(const std::string &type, const std::string &message) {
        std::cout << "[" << type << "] " << std::chrono::system_clock::now() << ": " << message << std::endl;
    }

    void Logger::INFO(const std::string &message) {
        InternalPrint("INFO", message);
    }

    void Logger::WARN(const std::string &message) {
        InternalPrint("WARN", message);
    }

    void Logger::ERROR(const std::string &message) {
        InternalPrint("ERROR", message);
    }

    void Logger::CRITICAL(const std::string &message) {
        InternalPrint("CRITICAL", message);
        std::exit(-1);
    }

    void Logger::CHECK(const bool test, const std::string &message) {
        if (test) {
            ERROR(message);
        }
    }

    void Logger::PANIC(const bool test, const std::string &message) {
        if (test) {
            CRITICAL(message);
        }
    }
}
