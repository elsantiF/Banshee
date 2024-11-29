#pragma once

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

// TODO: Add a way to log to a file
// TODO: Add preprocessor directives to enable/disable logging
namespace Banshee {
    using String = std::string;

    enum LogType {
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    class Logger {
        static fmt::color GetColor(LogType type);
        static String GetLogTypeString(LogType type);

        static void InternalPrint(LogType type, const String &message);

    public:
        static void INFO(const String &message);
        static void WARN(const String &message);
        static void ERROR(const String &message);
        static void CRITICAL(const String &message);
        static void CHECK(bool test, const String &message);
        static void PANIC(bool test, const String &message);
    };
}
