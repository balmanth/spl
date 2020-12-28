/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

namespace SPL::Metadata {
  /// <summary>
  /// Class metadata.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  class Class {
  private:
    // Accept any other value.
    template<typename>
    constexpr static bool Resolver(...) { return false; }
    // Accept only classes.
    template<typename U>
    constexpr static bool Resolver(int U::*) { return true; }
  public:
    /// <summary>
    /// Determines whether or not the given type is a class.
    /// </summary>
    constexpr static bool Is = Resolver<T>(nullptr) == true;
  };
  /// <summary>
  /// Determines whether or not the given type is a class.
  /// </summary>
  /// <typeparam name="T">Type.</typeparam>
  template<typename T>
  constexpr bool IsClass = Class<T>::Is;
}
