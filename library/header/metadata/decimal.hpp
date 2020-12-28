/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Decimal metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Decimal {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection { constexpr static bool State = false; };
    // Accept only floating point.
    template<>
    struct Reflection<float> { constexpr static bool State = true; };
    // Accept only double floating point.
    template<>
    struct Reflection<double> { constexpr static bool State = true; };
    // Accept only long double floating point.
    template<>
    struct Reflection<long double> { constexpr static bool State = true; };
    // Accept any constant value (and redirect as non-constant).
    template<typename U>
    struct Reflection<const U> : Reflection<U> { };
  public:
    /// <summary>
    /// Determines whether or not the given type is a decimal type.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
    /// <summary>
    /// Determines whether or not the specified type is convertible to decimal.
    /// </summary>
    constexpr static bool Convertible = Is;
  };
  /// <summary>
  /// Determines whether or not the given type is a decimal type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsDecimal = Decimal<T>::Is;
  /// <summary>
  /// Determines whether or not the given type is convertible to decimal.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsDecimalConvertible = Decimal<T>::Convertible;
}
