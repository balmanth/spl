/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../metadata/device.hpp"
#include "./types.hpp"

namespace SPL {
  /// <summary>
  /// Get the new nearest power of two based on the given value.
  /// </summary>
  /// <param name="value">Number value.</param>
  /// <returns>Returns the nearest power of two.</returns>
  inline Size NP2(Size value) {
    value--;
    for (Size bit = 1; bit < Metadata::Device::Bit; bit *= 2) {
      value |= value >> bit;
    }
    return ++value;
  }
}
