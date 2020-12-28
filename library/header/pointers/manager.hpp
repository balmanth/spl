/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Pointers {
  /// <summary>
  /// Pointer manager class.
  /// </summary>
  template<typename T>
  class Manager final {
  private:
    /// <summary>
    /// Pointer value.
    /// </summary>
    T* value;
    /// <summary>
    /// Number of references to the pointer value.
    /// </summary>
    Size references;
    /// <summary>
    /// Number of validations to the pointer manager.
    /// </summary>
    Size validations;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <param name="value">Pointer value.</param>
    Manager(T* const value) :
      value(value), references(1), validations(1) {}
    /// <summary>
    /// Get the pointer value.
    /// </summary>
    /// <returns>Returns the pointer value.</returns>
    T* getValue() const {
      return this->value;
    }
    /// <summary>
    /// Get the number of references to the pointer.
    /// </summary>
    /// <returns>Returns the current number of references to the pointer.</returns>
    Size getReferences() const {
      return this->references;
    }
    /// <summary>
    /// Increase the reference counting for the pointer value.
    /// </summary>
    void reference() {
      this->references++;
      this->validations++;
    }
    /// <summary>
    /// Decrease the reference counting for the pointer value.
    /// </summary>
    void dereference() {
      if (--this->references == 0) {
        delete this->value;
      }
      if (--this->validations == 0) {
        delete this;
      }
    }
    /// <summary>
    /// Increase the validation counting for the pointer manager.
    /// </summary>
    void validate() {
      this->validations++;
    }
    /// <summary>
    /// Decrease the validation counting for the pointer manager.
    /// </summary>
    void invalidate() {
      if (--this->validations == 0) {
        delete this;
      }
    }
  };
}
