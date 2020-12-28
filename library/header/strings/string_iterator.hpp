/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Strings {
  /// <summary>
  /// String iterator class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class StringIterator : public Iterator<T> {
  private:
    /// <summary>
    /// Basic string type.
    /// </summary>
    using BasicType = BasicString<T>;
    /// <summary>
    /// Basic string reference.
    /// </summary>
    const BasicType& string;
    /// <summary>
    /// Current index.
    /// </summary>
    Index index;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="string">Initial string.</param>
    StringIterator(const BasicType& string) :
      string(string), index(0) {}
  public:
    /// <summary>
    /// Check whether or not the iterator has the next character.
    /// </summary>
    /// <returns>Returns true when the next character exists, false otherwise.</returns>
    bool hasNext() const override {
      return this->index < this->string.getLength();
    }
    /// <summary>
    /// Move to the next character and get the current one.
    /// </summary>
    /// <returns>Returns the current character.</returns>
    /// <exception cref="SPL::Exceptions::InvalidOperation">Throws when there's no next character.</exception>
    const T& next() override {
      if (!this->hasNext()) {
        throw Exceptions::InvalidOperation();
      }
      return this->string[this->index++];
    }
  };
}
