/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../metadata/device.hpp"
#include "../types/select.hpp"

namespace SPL {
  /// <summary>
  /// Size type.
  /// </summary>
  using Size = unsigned int;
  /// <summary>
  /// Index type.
  /// </summary>
  using Index = unsigned int;
  /// <summary>
  /// Id type.
  /// </summary>
  using Id = Types::SelectType<Metadata::Device::x64, unsigned long long int, unsigned long int>;
}
