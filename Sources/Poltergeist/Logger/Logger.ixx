module;
#include <fmt/color.h>

export module Poltergeist.Logger;

import Poltergeist.String;

export enum LogType {
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

export class Logger {
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
