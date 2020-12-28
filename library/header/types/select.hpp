/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Types {
  /// <summary>
  /// Select type, helper class.
  /// </summary>
  /// <typeparam name="E">Expression value.</typeparam>
  /// <typeparam name="S">Success type.</typeparam>
  /// <typeparam name="F">Failure type.</typeparam>
  template<bool E, typename S, typename F>
  class Select {
  private:
    // Reflection declaration.
    template<bool, typename, typename>
    struct Resolver;
    // Accept only true expressions.
    template<typename S, typename F>
    struct Resolver<true, S, F> {
      using Type = S;
      constexpr static bool State = true;
    };
    // Accept only false expressions.
    template<typename S, typename F>
    struct Resolver<false, S, F> {
      using Type = F;
      constexpr static bool State = false;
    };
  public:
    /// <summary>
    /// Selected type.
    /// </summary>
    using Type = typename Resolver<E, S, F>::Type;
    /// <summary>
    /// Determines whether or not the given expression is true.
    /// </summary>
    constexpr static bool State = Resolver<E, S, F>::State;
  };
  /// <summary>
  /// Select the type according to the given expression value.
  /// </summary>
  /// <typeparam name="E">Expression value.</typeparam>
  /// <typeparam name="S">Success type.</typeparam>
  /// <typeparam name="F">Failure type.</typeparam>
  template<bool E, typename S, typename F>
  using SelectType = typename Select<E, S, F>::Type;
}
