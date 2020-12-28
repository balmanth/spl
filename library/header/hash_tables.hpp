/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./hash_tables/hash_function.hpp"
#include "./hash_tables/hash_map.hpp"
#include "./hash_tables/hash_set.hpp"

namespace SPL {
  /// <summary>
  /// Hash map class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  /// <typeparam name="H">Hash function.</typeparam>
  template<typename K, typename V, Id(H)(const K&) = &HashTables::Function>
  using HashMap = HashTables::HashMap<K, V, H>;
  /// <summary>
  /// Hash set class.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="H">Hash function.</typeparam>
  template<typename T, Id(H)(const T&) = &HashTables::Function>
  using HashSet = HashTables::HashSet<T, H>;
}
