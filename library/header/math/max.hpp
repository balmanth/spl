/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Math {
  /// <summary>
  /// Get the maximum value between the given ones.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="...N">Next types.</typeparam>
  /// <param name="first">First value.</param>
  /// <param name="second">Second value.</param>
  /// <param name="...next">Next values.</param>
  /// <returns>Returns the maximum value.</returns>
  template<typename T, typename ...N>
  constexpr T Max(const T& first, const T& second, const N& ...next) {
    if constexpr (sizeof...(next) > 0) {
      return Max(Max(first, second), next...);
    }
    return first > second ? first : second;
  }
}
