/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./same.hpp"

namespace SPL::Types {
  /// <summary>
  /// Base of, helper class.
  /// </summary>
  /// <typeparam name="B">Base type.</typeparam>
  /// <typeparam name="...T">Derived types.</typeparam>
  template<typename B, typename ...T>
  class BaseOf {
  private:
    // State types.
    struct Success {};
    struct Failure {};
    // Accept empty comparisons.
    template<typename...>
    struct Resolver {
      constexpr static bool State = false;
    };
    // Accept only base and derived classes.
    template<typename D>
    struct Resolver<D> {
      struct Object {
        operator B* () const;
        operator D* ();
      };
      template<typename I>
      constexpr static Success Test(D*, I);
      constexpr static Failure Test(B*, int);
      constexpr static bool State = AreSame<Success, decltype(Test(Object(), 0))>;
    };
    // Accept the base type, derived type and the remaining ones.
    template<typename D, typename ...R>
    struct Resolver<D, R...> {
      constexpr static bool State = Resolver<D>::State && Resolver<R...>::State;
    };
  public:
    /// <summary>
    /// Determines whether or not the first type is base of the derived types.
    /// </summary>
    constexpr static bool State = Resolver<T...>::State;
  };
  /// <summary>
  /// Determines whether or not the first type is base of the derived types.
  /// </summary>
  /// <typeparam name="B">Base type.</typeparam>
  /// <typeparam name="...T">Derived types.</typeparam>
  template<typename B, typename ...T>
  constexpr bool IsBaseOf = BaseOf<B, T...>::State;
}
