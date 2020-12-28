/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"

namespace SPL {
  /// <summary>
  /// Hash interface.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Hash {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Hash() = default;
  public:
    /// <summary>
    /// Get the current hash.
    /// </summary>
    /// <returns>Returns the current hash.</returns>
    virtual Id getHash() const = 0;
    /// <summary>
    /// Generate the next hash based on the given value.
    /// </summary>
    /// <param name="value">Value for the next hash.</param>
    virtual void next(const T& value) = 0;
  };
}
