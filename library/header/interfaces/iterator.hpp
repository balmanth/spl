/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL {
  /// <summary>
  /// Iterator interface.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Iterator {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Iterator() = default;
  public:
    /// <summary>
    /// Check whether or not the iterator has the next value.
    /// </summary>
    /// <returns>Returns true when the next value exists, false otherwise.</returns>
    virtual bool hasNext() const = 0;
    /// <summary>
    /// Move to the next value and get the current one.
    /// </summary>
    /// <returns>Returns the current value.</returns>
    virtual const T& next() = 0;
  };
}
