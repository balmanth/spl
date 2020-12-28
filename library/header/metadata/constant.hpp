/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Constant metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Constant {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection {
      // Constant type.
      using Type = U;
      // Constant state.
      constexpr static bool State = false;
    };
    // Accept only constants.
    template<typename U>
    struct Reflection<const U> : Reflection<U> {
      // Constant state.
      constexpr static bool State = true;
    };
  public:
    /// <summary>
    /// Constant type.
    /// </summary>
    using Type = typename Reflection<T>::Type;
    /// <summary>
    /// Determines whether or not the given type is constant.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
  };
  /// <summary>
  /// Extract the constant type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  using ConstantType = typename Constant<T>::Type;
  /// <summary>
  /// Determines whether or not the given type is constant.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsConstant = Constant<T>::Is;
}
