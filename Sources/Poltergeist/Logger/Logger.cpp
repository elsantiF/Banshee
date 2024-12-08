module;
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

module Poltergeist.Logger;

fmt::color Logger::GetColor(const LogType type) {
    switch (type) {
        case LogType::INFO:
            return fmt::color::green;
        case LogType::WARN:
            return fmt::color::yellow;
        case LogType::ERROR:
        case LogType::CRITICAL:
            return fmt::color::red;
    }

    // This should never happen, put it here to avoid warnings
    return fmt::color::white;
}

String Logger::GetLogTypeString(const LogType type) {
    switch (type) {
        case LogType::INFO:
            return "INFO";
        case LogType::WARN:
            return "WARN";
        case LogType::ERROR:
            return "ERROR";
        case LogType::CRITICAL:
            return "CRITICAL";
    }

    // This should never happen, put it here to avoid warnings
    return "UNKNOWN";
}

void Logger::InternalPrint(const LogType type, const String &message) {
    const auto time = std::chrono::system_clock::now();
    auto strType = GetLogTypeString(type);
    fmt::print(fg(GetColor(type)), "{:%d-%m-%Y %H:%M:%S} [{}]: {}\n", time, strType, message);
}

void Logger::INFO(const String &message) {
    InternalPrint(LogType::INFO, message);
}

void Logger::WARN(const String &message) {
    InternalPrint(LogType::WARN, message);
}

void Logger::ERROR(const String &message) {
    InternalPrint(LogType::ERROR, message);
}

void Logger::CRITICAL(const String &message) {
    InternalPrint(LogType::CRITICAL, message);
    std::exit(-1);
}

void Logger::CHECK(const bool test, const String &message) {
    if (test) {
        ERROR(message);
    }
}

void Logger::PANIC(const bool test, const String &message) {
    if (test) {
        CRITICAL(message);
    }
}
