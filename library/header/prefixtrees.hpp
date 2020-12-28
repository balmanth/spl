/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./prefixtrees/map.hpp"
#include "./prefixtrees/set.hpp"

namespace SPL {
  /// <summary>
  /// Prefix Map.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  using PrefixMap = PrefixTrees::Map<K, V>;
  /// <summary>
  /// Prefix Set.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  using PrefixSet = PrefixTrees::Set<T>;
}
