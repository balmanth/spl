/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL {
  /// <summary>
  /// Copy the given source to the given target.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="source">Source array.</param>
  /// <param name="target">Target array.</param>
  /// <param name="length">Copy length.</param>
  /// <returns>Returns the target array.</returns>
  template<typename T>
  T* Copy(const T source[], T target[], const Size length) {
    for (Size offset = 0; offset < length; ++offset) {
      target[offset] = source[offset];
    }
    return target;
  }
}
