/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../metadata/reference.hpp"

namespace SPL {
  /// <summary>
  /// Try to cast the given value to an rvalue reference type.
  /// Allows the value to be moved (by forwarding it) if implemented for this purpose.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="value">Value to forward.</param>
  /// <returns>Returns the given value.</returns>
  template<typename T>
  constexpr T&& Forward(Metadata::ReferenceType<T>& value) noexcept {
    return static_cast<T&&>(value);
  }
  /// <summary>
  /// Try to cast the given value to an rvalue reference type.
  /// Allows the value to be moved (by forwarding it) if implemented for this purpose.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="value">Value to forward.</param>
  /// <returns>Returns the given value.</returns>
  template<typename T>
  constexpr T&& Forward(Metadata::ReferenceType<T>&& value) noexcept {
    static_assert(!Metadata::IsLValueReference<T>, "Can't forward an rvalue as an lvalue.");
    return static_cast<T&&>(value);
  }
}
