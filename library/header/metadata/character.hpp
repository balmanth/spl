/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Character metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Character {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection { constexpr static bool State = false; };
    // Accept only wide characters.
    template<>
    struct Reflection<wchar_t> { constexpr static bool State = true; };
    // Accept only UTF-16 characters.
    template<>
    struct Reflection<char16_t> { constexpr static bool State = true; };
    // Accept only UTF-32 characters.
    template<>
    struct Reflection<char32_t> { constexpr static bool State = true; };
    // Accept only 8-bit characters.
    template<>
    struct Reflection<char> { constexpr static bool State = true; };
    // Accept only 8-bit signed characters.
    template<>
    struct Reflection<signed char> { constexpr static bool State = true; };
    // Accept only 8-bit unsigned characters.
    template<>
    struct Reflection<unsigned char> { constexpr static bool State = true; };
    // Accept any constant value (and redirect as non-constant).
    template<typename U>
    struct Reflection<const U> : Reflection<U> { };
  public:
    /// <summary>
    /// Determines whether or not the given type is a character type.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
    /// <summary>
    /// Determines whether or not the specified type is convertible to character.
    /// </summary>
    constexpr static bool Convertible = Is;
  };
  /// <summary>
  /// Determines whether or not the given type is a character type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsCharacter = Character<T>::Is;
  /// <summary>
  /// Determines whether or not the given type is convertible to character.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsCharacterConvertible = Character<T>::Convertible;
}
