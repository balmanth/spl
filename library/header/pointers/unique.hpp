/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Pointers {
  /// <summary>
  /// Unique pointer class.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Unique final {
  private:
    /// <summary>
    /// Pointer to the value.
    /// </summary>
    T* pointer;
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Unique<T>& source, Unique<T>& target) noexcept {
      using SPL::Swap;
      Swap(source.pointer, target.pointer);
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <param name="pointer">Initial pointer.</param>
    explicit Unique(T* const pointer = nullptr) :
      pointer(pointer) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Unique(Unique<T>&& other) noexcept : Unique() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Unique() {
      this->release();
    }
  public:
    /// <summary>
    /// Release the pointer.
    /// </summary>
    void release() {
      delete this->pointer;
      this->pointer = nullptr;
    }
  public:
    /// <summary>
    /// Test if the pointer isn't null.
    /// </summary>
    /// <returns>Returns true when the pointer isn't null, false otherwise.</returns>
    operator bool() const {
      return this->pointer != nullptr;
    }
    /// <summary>
    /// Dereference the pointer.
    /// </summary>
    /// <returns>Returns the pointer value.</returns>
    T& operator * () const {
      return *this->pointer;
    }
    /// <summary>
    /// Access members of the pointer.
    /// </summary>
    /// <returns>Returns the pointer.</returns>
    T* operator -> () const {
      return this->pointer;
    }
    /// <summary>
    /// Access indexes of the pointer.
    /// </summary>
    /// <param name="index">Pointer index.</param>
    /// <returns>Returns a references to the pointer index.</returns>
    T& operator [] (const Index index) const {
      return this->pointer[index];
    }
    /// <summary>
    /// Assign all properties from the given pointer.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Unique<T>& operator = (Unique<T> other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
}
