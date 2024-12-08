module;
#include <map>
#include <unordered_map>
#include <vector>

export module Poltergeist.Container;

export template <typename T>
using Vector = std::vector<T>;

export template <typename K, typename V>
using Map = std::map<K, V>;

export template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

export template <typename T, typename U>
using Pair = std::pair<T, U>; // Is not a "container" but it's used in the same way
