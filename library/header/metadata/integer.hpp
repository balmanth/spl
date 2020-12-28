/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./character.hpp"
#include "./decimal.hpp"

namespace SPL::Metadata {
  /// <summary>
  /// Integer metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Integer {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection { constexpr static bool State = false; };
    // Accept only boolean values.
    template<>
    struct Reflection<bool> { constexpr static bool State = true; };
    // Accept only short integer values.
    template<>
    struct Reflection<signed short int> { constexpr static bool State = true; };
    // Accept only integer values.
    template<>
    struct Reflection<signed int> { constexpr static bool State = true; };
    // Accept only long integer values.
    template<>
    struct Reflection<signed long int> { constexpr static bool State = true; };
    // Accept only long long integer values.
    template<>
    struct Reflection<signed long long int> { constexpr static bool State = true; };
    // Accept only unsigned short integer values.
    template<>
    struct Reflection<unsigned short int> { constexpr static bool State = true; };
    // Accept only unsigned integer values.
    template<>
    struct Reflection<unsigned int> { constexpr static bool State = true; };
    // Accept only unsigned long integer values.
    template<>
    struct Reflection<unsigned long int> { constexpr static bool State = true; };
    // Accept only unsigned long long integer values.
    template<>
    struct Reflection<unsigned long long int> { constexpr static bool State = true; };
    // Accept any constant value (and redirect as non-constant).
    template<typename U>
    struct Reflection<const U> : Reflection<U> { };
  public:
    /// <summary>
    /// Determines whether or not the given type is an integer type.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
    /// <summary>
    /// Determines whether or not the given type is convertible to integer.
    /// </summary>
    constexpr static bool Convertible = Is || Decimal<T>::Convertible || Character<T>::Convertible;
  };
  /// <summary>
  /// Determines whether or not the given type is an integer type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsInteger = Integer<T>::Is;
  /// <summary>
  /// Determines whether or not the given type is convertible to integer.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsIntegerConvertible = Integer<T>::Convertible;
}
