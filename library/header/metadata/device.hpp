/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Device metadata.
  /// </summary>
  class Device {
  public:
    /// <summary>
    /// Stores the current bit version.
    /// </summary>
    constexpr static int Bit = (sizeof(void*) * 8);
    /// <summary>
    /// Determines whether or not the current device is x86.
    /// </summary>
    constexpr static bool x86 = (Device::Bit == 32);
    /// <summary>
    /// Determines whether or not the current device is x64.
    /// </summary>
    constexpr static bool x64 = (Device::Bit == 64);
  };
}
