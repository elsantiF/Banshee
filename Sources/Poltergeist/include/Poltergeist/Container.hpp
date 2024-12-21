#pragma once

#include <map>
#include <unordered_map>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template <typename T, typename U>
using Pair = std::pair<T, U>; // Is not a "container" but it's used in the same way
