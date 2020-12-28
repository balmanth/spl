/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Types {
  /// <summary>
  /// Enable type, helper class.
  /// </summary>
  /// <typeparam name="E">Expression value.</typeparam>
  /// <typeparam name="T">Type.</typeparam>
  template<bool E, typename T>
  class Enable {
  public:
    /// <summary>
    /// Determines whether or not the given expression is true.
    /// </summary>
    constexpr static bool State = false;
  };
  /// <summary>
  /// Enable type, helper class.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Enable<true, T> {
  public:
    /// <summary>
    /// Enabled type.
    /// </summary>
    using Type = typename T;
    /// <summary>
    /// Determines whether or not the given expression is true.
    /// </summary>
    constexpr static bool State = true;
  };
  /// <summary>
  /// Enable the type according to the given expression value.
  /// </summary>
  /// <typeparam name="E">Expression value.</typeparam>
  /// <typeparam name="T">Type.</typeparam>
  template<bool E, typename T = void*>
  using EnableType = typename Enable<E, T>::Type;
}
