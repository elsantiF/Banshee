#pragma once

#include <string>
#include <utility>
#include <filesystem>

#include <Poltergeist/Poltergeist.h>

namespace Banshee {
    using namespace Poltergeist;

#pragma region Utilities
    using String = std::string;
#pragma endregion

#pragma region Filesystem
    namespace fs = std::filesystem;
#pragma endregion
}
