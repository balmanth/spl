/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"

namespace SPL::Types {
  /// <summary>
  /// Pick type, helper class.
  /// </summary>
  /// <typeparam name="I">Type index.</typeparam>
  /// <typeparam name="...T">Types.</typeparam>
  template<Index I, typename ...T>
  class Pick {
    static_assert(sizeof...(T) > 0, "One or more T types must be given.");
  private:
    // Resolver declaration.
    template<Index I, typename...>
    struct Resolver;
    // Accept only the desired index and type.
    template<typename U, typename ...R>
    struct Resolver<0, U, R...> {
      using Type = U;
    };
    // Accept any index and type.
    template<Index I, typename U, typename ...R>
    struct Resolver<I, U, R...> {
      using Type = typename Resolver<I - 1, R...>::Type;
    };
  public:
    /// <summary>
    /// Picked type.
    /// </summary>
    using Type = typename Resolver<I, T...>::Type;
  };
  /// <summary>
  /// Pick the type that corresponds to the given index.
  /// </summary>
  /// <typeparam name="I">Desired type index.</typeparam>
  /// <typeparam name="...T">Types.</typeparam>
  template<Index I, typename ...T>
  using PickType = typename Pick<I, T...>::Type;
}
