/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../interfaces/comparable.hpp"
#include "../metadata/pointer.hpp"
#include "../metadata/integer.hpp"
#include "../types/base_of.hpp"
#include "./types.hpp"

namespace SPL {
  /// <summary>
  /// Compare the given source with the given target.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="source">Source value.</param>
  /// <param name="target">Target value.</param>
  /// <returns>
  /// Returns -1 when the given source is less than the given target.
  /// Returns  0 when the given source is equals to the given target.
  /// Returns  1 when the given source is greater than the given target.
  /// </returns>
  template<typename T>
  int Compare(const T& source, const T& target) {
    if constexpr (Types::IsBaseOf<Comparable<T>, T>) {
      return source.compare(target);
    }
    else if constexpr (!Metadata::IsPointer<T> && !Metadata::IsIntegerConvertible<T>) {
      return Compare(&source, &target);
    }
    else if (source < target) {
      return -1;
    }
    else if (source > target) {
      return 1;
    }
    return 0;
  }
  /// <summary>
  /// Compare the given source with the given target using the specified length.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <param name="source">Source array.</param>
  /// <param name="target">Target array.</param>
  /// <param name="length">Comparison length.</param>
  /// <returns>
  /// Returns -1 when the given source is less than the given target.
  /// Returns  0 when the given source is equals to the given target.
  /// Returns  1 when the given source is greater than the given target.
  /// </returns>
  template<typename T>
  int Compare(const T source[], const T target[], const Size length) {
    if (source != nullptr && target != nullptr) {
      for (Size offset = 0; offset < length; ++offset) {
        const int result = Compare(source[offset], target[offset]);
        if (result != 0) {
          return result;
        }
      }
    }
    else if (source != nullptr) {
      return 1;
    }
    else if (target != nullptr) {
      return -1;
    }
    return 0;
  }
}
