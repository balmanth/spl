/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Arrays {
  /// <summary>
  /// Array iterator class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  class ArrayIterator : public Iterator<T> {
  private:
    /// <summary>
    /// Basic array type.
    /// </summary>
    using BasicType = BasicArray<T>;
    /// <summary>
    /// Basic array reference.
    /// </summary>
    const BasicType& array;
    /// <summary>
    /// Current index.
    /// </summary>
    Index index;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="array">Initial array.</param>
    explicit ArrayIterator(const BasicType& array) :
      array(array), index(0) {}
  public:
    /// <summary>
    /// Check whether or not the iterator has a next element.
    /// </summary>
    /// <returns>Returns true when the next element exists, false otherwise.</returns>
    bool hasNext() const override {
      return this->index < this->array.getLength();
    }
    /// <summary>
    /// Move to the next element and get the current one.
    /// </summary>
    /// <returns>Returns the current element.</returns>
    /// <exception cref="SPL::Exceptions::InvalidOperation">Throws when there's no next element.</exception>
    const T& next() override {
      if (!this->hasNext()) {
        throw Exceptions::InvalidOperation();
      }
      return this->array[this->index++];
    }
  };
}
