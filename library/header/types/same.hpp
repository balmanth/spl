/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Types {
  /// <summary>
  /// Same type, helper class.
  /// </summary>
  /// <typeparam name="E">Expected type.</typeparam>
  /// <typeparam name="...T">Comparison types.</typeparam>
  template<typename E, typename ...T>
  class Same {
  private:
    // Accept only different types.
    template<typename...>
    struct Resolver {
      constexpr static bool State = false;
    };
    // Accept only equal types.
    template<typename U>
    struct Resolver<U, U> {
      constexpr static bool State = true;
    };
    // Accept only equal and next types.
    template<typename U, typename ...R>
    struct Resolver<U, U, R...> {
      constexpr static bool State = Resolver<U, R...>::State;
    };
  public:
    /// <summary>
    /// Determines whether or not the given types are the same as expected.
    /// </summary>
    constexpr static bool State = Resolver<E, T...>::State;
  };
  /// <summary>
  /// Determines whether or not the given types are the same as expected.
  /// </summary>
  /// <typeparam name="E">Expected type.</typeparam>
  /// <typeparam name="...T">Comparison types.</typeparam>
  template<typename E, typename ...T>
  constexpr bool AreSame = Same<E, T...>::State;
}
