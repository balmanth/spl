/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Pointer metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Pointer {
  private:
    // Accept any other value.
    template<typename U>
    struct Reflection {
      // Pointer type.
      using Type = U;
      // Pointer state.
      constexpr static bool State = false;
    };
    // Accept only pointers.
    template<typename U>
    struct Reflection<U*> : public Reflection<U> {
      // Pointer state.
      constexpr static bool State = true;
    };
  public:
    /// <summary>
    /// Pointer type.
    /// </summary>
    using Type = typename Reflection<T>::Type;
    /// <summary>
    /// Determines whether or not the given type is a pointer.
    /// </summary>
    constexpr static bool Is = Reflection<T>::State;
  };
  /// <summary>
  /// Extract the pointer type.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  using PointerType = typename Pointer<T>::Type;
  /// <summary>
  /// Determines whether or not the given type is a pointer.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsPointer = Pointer<T>::Is;
}
