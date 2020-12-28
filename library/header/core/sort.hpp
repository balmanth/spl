/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./compare.hpp"
#include "./swap.hpp"

namespace SPL {
  /// <summary>
  /// Default sort function.
  /// This function uses the Quicksort algorithm. For more info, please visit:
  /// https://en.wikipedia.org/wiki/Quicksort
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="C">Comparator function.</typeparam>
  /// <param name="array">Array of values.</param>
  /// <param name="start">Start offset.</param>
  /// <param name="end">End offset.</param>
  template<typename T, int(C)(const T&, const T&) = &Compare>
  void Sort(T array[], Size start, Size end) {
    Size middle = (start + end) / 2;
    Size offset = start;
    Size bounds = end;
    while (offset <= bounds) {
      while (C(array[offset], array[middle]) < 0) {
        offset++;
      }
      while (C(array[bounds], array[middle]) > 0) {
        bounds--;
      }
      if (offset <= bounds) {
        Swap(array[offset++], array[bounds--]);
      }
    }
    if (start < bounds) {
      Sort<T, C>(array, start, bounds);
    }
    if (offset < end) {
      Sort<T, C>(array, offset, end);
    }
  }
}
