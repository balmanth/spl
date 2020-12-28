/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core.hpp"
#include "../interfaces.hpp"
#include "../exceptions.hpp"
#include "../metadata.hpp"

namespace SPL::PrefixTrees {
  /// <summary>
  /// Base class declaration.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="...V">Value types for specialization.</typeparam>
  template<typename K, typename ...V>
  class Base;
  /// <summary>
  /// Node class declaration.
  /// </summary>
  /// <typeparam name="...T">Types for specialization...</typeparam>
  template<typename ...T>
  class Node;
}
