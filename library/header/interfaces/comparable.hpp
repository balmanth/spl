/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL {
  /// <summary>
  /// Comparable interface.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Comparable {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Comparable() = default;
  public:
    /// <summary>
    /// Compare both objects.
    /// </summary>
    /// <param name="other">Other object.</param>
    /// <returns>
    /// Returns -1 when this object is less than the other one.
    /// Returns  0 when this object is equals to the other one.
    /// Returns  1 when this object is greater than the other one.
    /// </returns>
    virtual int compare(const T& other) const = 0;
  };
}
