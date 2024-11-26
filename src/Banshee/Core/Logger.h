#pragma once

#include <iostream>
#include <chrono>

// TODO: Add a way to log to a file
// TODO: Add preprocessor directives to enable/disable logging
namespace Banshee {
    class Logger {
        static void InternalPrint(const std::string &type, const std::string &message);

    public:
        static void INFO(const std::string &message);
        static void WARN(const std::string &message);
        static void ERROR(const std::string &message);
        static void CRITICAL(const std::string &message);
        static void CHECK(bool test, const std::string &message);
        static void PANIC(bool test, const std::string &message);
    };
}
