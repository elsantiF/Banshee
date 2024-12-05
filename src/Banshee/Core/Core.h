#pragma once

#include <string>
#include <utility>

#include <GSL.h>

#include "Logger.h"

namespace Banshee {
    using namespace GSL;

#pragma region Utilities
    using String = std::string;
#pragma endregion

#pragma region Filesystem
    namespace fs = std::filesystem;
#pragma endregion
}
