/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core.hpp"

namespace SPL::Pointers {
  /// <summary>
  /// Unique pointer declaration.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Unique;
  /// <summary>
  /// Shared pointer declaration.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Shared;
  /// <summary>
  /// Weak pointer declaration.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Weak;
}
