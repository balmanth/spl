/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./manager.hpp"

namespace SPL::Pointers {
  /// <summary>
  /// Shared pointer class.
  /// </summary>
  /// <typeparam name="T">Pointer type.</typeparam>
  template<typename T>
  class Shared final {
    // Friend weak pointer class.
    friend class Weak<T>;
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
    Shared(Manager<T>* const pointer) : pointer(pointer) {
      if (this->pointer != nullptr) {
        this->pointer->reference();
      }
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <param name="pointer">Value pointer.</param>
    explicit Shared(T* const pointer = nullptr) :
      pointer(pointer ? new Manager<T>(pointer) : nullptr) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Shared(const Shared<T>& other) :
      Shared(other.pointer) {}
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Shared() {
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
        this->pointer->dereference();
        this->pointer = nullptr;
      }
    }
  public:
    /// <summary>
    /// Alias for the isValid method.
    /// </summary>
    operator bool() const {
      return this->isValid();
    }
    /// <summary>
    /// Access members of the pointer.
    /// This method doesn't check whether the pointer is valid or not.
    /// </summary>
    /// <returns>Returns the pointer.</returns>
    T* operator ->() const {
      return this->pointer->getValue();
    }
    /// <summary>
    /// Dereference the pointer.
    /// This method doesn't check whether the pointer is valid or not.
    /// </summary>
    /// <returns>Returns the pointer value.</returns>
    T& operator *() const {
      return *this->pointer->getValue();
    }
    /// <summary>
    /// Access indexes of the pointer.
    /// This method doesn't check whether the pointer is valid or not.
    /// </summary>
    /// <param name="index">Pointer index.</param>
    /// <returns>Returns a references to the pointer index.</returns>
    T& operator [] (const Index index) const {
      return this->pointer->getValue()[index];
    }
    /// <summary>
    /// Assign all properties from the given pointer.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Shared<T>& operator = (const Shared<T>& other) noexcept {
      this->release();
      if ((this->pointer = other.pointer) != nullptr) {
        this->pointer->reference();
      }
      return *this;
    }
  };
}
