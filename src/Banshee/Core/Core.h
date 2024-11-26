#pragma once

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>

#include "Logger.h"

namespace Banshee {
#pragma region Memory Macros
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
#pragma endregion

#pragma region Container Macros
    template<typename T>
    using Vector = std::vector<T>;

    template<typename K, typename V>
    using Map = std::map<K, V>;

    template<typename K, typename V>
    using UnorderedMap = std::unordered_map<K, V>;

    template<typename T, typename U>
    using Pair = std::pair<T, U>; // Is not a "container" but it's used in the same way
#pragma endregion

#pragma region Utilities
    using String = std::string;
#pragma endregion

#pragma region Filesystem
    namespace fs = std::filesystem;
#pragma endregion
}
