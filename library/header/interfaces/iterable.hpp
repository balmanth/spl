/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../pointers/unique.hpp"
#include "./iterator.hpp"

namespace SPL {
  /// <summary>
  /// Iterable interface.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Iterable {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Iterable() = default;
  public:
    /// <summary>
    /// Get a new iterator.
    /// </summary>
    /// <returns>Returns the new iterator.</returns>
    virtual Pointers::Unique<Iterator<T>> getIterator() const = 0;
  };
}
