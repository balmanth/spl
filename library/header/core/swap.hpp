/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./move.hpp"

namespace SPL {
  /// <summary>
  /// Exchange the given target and source.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="source">Source value.</param>
  /// <param name="target">Target value.</param>
  template<typename T>
  void Swap(T& source, T& target) noexcept {
    T temp(Move(source));
    source = Move(target);
    target = Move(temp);
  }
}
