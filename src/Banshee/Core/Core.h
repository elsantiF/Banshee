#pragma once

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>

#include <cstdint>

#include "Logger.h"

namespace Banshee {
#pragma region Numeric Types
    using i8 = signed char;
    using i16 = short;
    using i32 = int;
    using i64 = long long;

    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;

    using f32 = float;
    using f64 = double;
#pragma endregion


#pragma region Memory Macros
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> MakeRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
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
