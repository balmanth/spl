/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"
#include "../metadata/constant.hpp"

namespace SPL {
  /// <summary>
  /// Set interface.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Set {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Set() = default;
  public:
    /// <summary>
    /// Get the number of values in the set.
    /// </summary>
    /// <returns>Returns the set size.</returns>
    virtual Size getSize() const = 0;
    /// <summary>
    /// Determines whether or not the set is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    virtual bool isEmpty() const = 0;
    /// <summary>
    /// Add the specified value in the set by using move semantics.
    /// </summary>
    /// <param name="value">Value.</param>
    virtual void add(Metadata::ConstantType<T>&& value) = 0;
    /// <summary>
    /// Add a copy of the specified value in the set.
    /// </summary>
    /// <param name="value">Value.</param>
    virtual void add(const T& value) = 0;
    /// <summary>
    /// Determines whether or not the set contains the specified value.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    virtual bool has(const T& value) const = 0;
    /// <summary>
    /// Remove the specified value from the set.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    virtual bool remove(const T& value) = 0;
    /// <summary>
    /// Clear the set.
    /// </summary>
    virtual void clear() = 0;
  };
}
