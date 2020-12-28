/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./pointers/unique.hpp"
#include "./pointers/shared.hpp"
#include "./pointers/weak.hpp"

namespace SPL {
  /// <summary>
  /// Unique Pointer.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  using Unique = Pointers::Unique<T>;
  /// <summary>
  /// Shared Pointer.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  using Shared = Pointers::Shared<T>;
  /// <summary>
  /// Weak Pointer.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  using Weak = Pointers::Weak<T>;
}
