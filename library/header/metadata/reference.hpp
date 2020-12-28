/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Reference metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Reference {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection {
      // Reference type.
      using Type = U;
      // Reference states.
      constexpr static bool State = false;
      constexpr static bool LVState = false;
      constexpr static bool RVState = false;
    };
    // Accept only lvalue references.
    template<typename U>
    struct Reflection<U&> : public Reflection<U> {
      // Reference states.
      constexpr static bool State = true;
      constexpr static bool LVState = true;
    };
    // Accept only rvalue references.
    template<typename U>
    struct Reflection<U&&> : public Reflection<U> {
      // Reference state.
      constexpr static bool State = true;
      constexpr static bool RVState = true;
    };
  public:
    /// <summary>
    /// Referenced type.
    /// </summary>
    using Type = typename Reflection<T>::Type;
    /// <summary>
    /// Determines whether or not the given type is a reference.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
    /// <summary>
    /// Determines whether or not the given type is an lvalue reference.
    /// </summary>
    constexpr static bool IsLValue = Reflection<T>::LVState;
    /// <summary>
    /// Determines whether or not the given type is an rvalue reference.
    /// </summary>
    constexpr static bool IsRValue = Reflection<T>::RVState;
  };
  /// <summary>
  /// Extract the reference type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  using ReferenceType = typename Reference<T>::Type;
  /// <summary>
  /// Determines whether or not the given type is a reference.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsReference = Reference<T>::Is;
  /// <summary>
  /// Determines whether or not the given type is an lvalue reference.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsLValueReference = Reference<T>::IsLValue;
  /// <summary>
  /// Determines whether or not the given type is an rvalue reference.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsRValueReference = Reference<T>::IsRValue;
}
