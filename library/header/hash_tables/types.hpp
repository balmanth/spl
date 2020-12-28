/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core.hpp"
#include "../math.hpp"
#include "../pointers.hpp"
#include "../interfaces.hpp"
#include "../exceptions.hpp"
#include "../metadata.hpp"
#include "../hashes.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Basic table class declaration.
  /// </summary>
  /// <typeparam name="H">Hash function.</typeparam>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="...V">Value types for specialization.</typeparam>
  template<auto H, typename K, typename ...V>
  class BasicTable;
  /// <summary>
  /// Hash entry class declaration.
  /// </summary>
  /// <typeparam name="...T">Types for specialization...</typeparam>
  template<typename ...T>
  class HashEntry;
  /// <summary>
  /// Unique iterator class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  using UniqueIterator = Unique<Iterator<T>>;
  /// <summary>
  /// Entry states enumeration.
  /// </summary>
  enum class EntryState {
    Free,
    Occupied,
    Deleted
  };
}
