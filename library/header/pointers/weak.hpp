/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./manager.hpp"

namespace SPL::Pointers {
  /// <summary>
  /// Weak pointer class.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Weak final {
  private:
    /// <summary>
    /// Pointer manager.
    /// </summary>
    Manager<T>* pointer;
  private:
    /// <summary>
    /// Internal constructor.
    /// </summary>
    /// <param name="pointer">Pointer manager.</param>
    Weak(Manager<T>* const pointer) : pointer(pointer) {
      if (this->pointer != nullptr) {
        this->pointer->validate();
      }
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Weak() :
      pointer(nullptr) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Weak(const Weak<T>& other) :
      Weak(other.pointer) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="other">Other pointer.</param>
    Weak(const Shared<T>& other) :
      Weak(other.pointer) {}
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Weak() {
      this->release();
    }
  public:
    /// <summary>
    /// Get the number of references to the pointer.
    /// </summary>
    /// <returns>Returns the current number of references.</returns>
    Size getReferences() const {
      if (this->pointer != nullptr) {
        return this->pointer->getReferences();
      }
      return 0;
    }
    /// <summary>
    /// Determines whether or not the pointer is valid.
    /// </summary>
    /// <returns>Returns true when the pointer is valid, false otherwise.</returns>
    bool isValid() const {
      return this->getReferences() > 0;
    }
    /// <summary>
    /// Release the pointer from memory.
    /// </summary>
    void release() {
      if (this->pointer != nullptr) {
        this->pointer->invalidate();
        this->pointer = nullptr;
      }
    }
    /// <summary>
    /// Get a new shared pointer.
    /// </summary>
    /// <returns>Returns the shared pointer.</returns>
    Shared<T> get() const {
      return Shared<T>(this->pointer);
    }
  public:
    /// <summary>
    /// Alias for the isValid method.
    /// </summary>
    operator bool() const {
      return this->isValid();
    }
    /// <summary>
    /// Assign all properties from the given pointer.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Weak<T>& operator = (const Weak<T>& other) noexcept {
      this->release();
      if ((this->pointer = other.pointer) != nullptr) {
        this->pointer->validate();
      }
      return *this;
    }
  };
}
