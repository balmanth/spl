/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types/enable.hpp"
#include "../types/base_of.hpp"
#include "./types.hpp"

namespace SPL {
  /// <summary>
  /// Pack class.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Pack final {
  private:
    /// <summary>
    /// Packed length.
    /// </summary>
    Size length;
    /// <summary>
    /// Packed pointers.
    /// </summary>
    const T** values;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Pack<T>& source, Pack<T>& target) noexcept {
      using SPL::Swap;
      Swap(source.length, target.length);
      Swap(source.values, target.values);
    }
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <typeparam name="...N">Value types.</typeparam>
    /// <param name="...values">Initial values.</param>
    template<typename ...N, typename Types::EnableType<Types::AreSame<T, N...> || Types::IsBaseOf<T, N...>> = nullptr>
    Pack(const N& ...values) :
      length(sizeof...(values)), values(new const T* [sizeof...(values)]{ &values... }) {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    Pack() :
      length(0), values(nullptr) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Pack(const Pack<T>& other) :
      length(other.length), values(other.length > 0 ? Copy(other.values, new const T * [other.length], other.length) : nullptr) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Pack(Pack<T>&& other) noexcept : Pack() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Pack() {
      delete this->values;
    }
  public:
    /// <summary>
    /// Get the pack length.
    /// </summary>
    /// <returns>Returns the packed length.</returns>
    Size getLength() const {
      return this->length;
    }
    /// <summary>
    /// Check whether or not the pack is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    bool isEmpty() const {
      return this->length == 0;
    }
    /// <summary>
    /// Get the pack value that corresponds to the given index.
    /// </summary>
    /// <param name="index">Zero based index.</param>
    /// <returns>Returns the corresponding value.</returns>
    const T& get(const Index index) const {
      return *(this->values[index]);
    }
  public:
    /// <summary>
    /// Get the pack value that corresponds to the given index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding value.</returns>
    const T& operator [](const Index index) const {
      return this->get(index);
    }
    /// <summary>
    /// Assign all properties from the given pack.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Pack<T>& operator = (Pack<T> other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
}
