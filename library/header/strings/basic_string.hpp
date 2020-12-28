/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Strings {
  /// <summary>
  /// Basic string class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class BasicString final {
  private:
    /// <summary>
    /// Array of characters.
    /// </summary>
    T* string;
    /// <summary>
    /// Current number of characters.
    /// </summary>
    Size length;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(BasicString& source, BasicString& target) noexcept {
      using SPL::Swap;
      Swap(source.string, target.string);
      Swap(source.length, target.length);
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    BasicString() :
      string(nullptr), length(0) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="length">Initial length.</param>
    BasicString(const Size length) :
      string(length > 0 ? new T[length]() : nullptr), length(length) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="string">Initial string.</param>
    /// <param name="length">Initial length.</param>
    BasicString(const T string[], const Size length) :
      string(length > 0 ? Copy(string, new T[length], length) : nullptr), length(length) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="string">Initial string.</param>
    template<Size N>
    BasicString(const T(&string)[N]) :
      BasicString(string, (string[N - 1] == T()) ? N - 1 : N) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicString(const BasicString& other) :
      BasicString(other.string, other.length) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicString(BasicString&& other) noexcept : BasicString() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~BasicString() {
      delete[] this->string;
    }
  public:
    /// <summary>
    /// Get the number of characters in the string.
    /// </summary>
    /// <returns>Returns the string length.</returns>
    Size getLength() const {
      return this->length;
    }
    /// <summary>
    /// Merge all the given strings into a new one.
    /// </summary>
    /// <param name="pack">Pack of strings.</param>
    /// <returns>Returns the new string.</returns>
    BasicString concat(const StringPack<T>& pack) const {
      auto capacity = this->length;
      for (Index index = 0; index < pack.getLength(); ++index) {
        capacity += pack[index].getLength();
      }
      BasicString string(capacity);
      Size offset = this->length;
      Copy(this->string, string.string, offset);
      for (Index index = 0; index < pack.getLength(); ++index) {
        const auto& current = pack[index];
        const auto length = current.getLength();
        Copy(&(current[0]), &string.string[offset], length);
        offset += length;
      }
      return string;
    }
    /// <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    T& get(const Index index) const {
      if (index >= this->length) {
        throw Exceptions::IndexOutOfBounds(index);
      }
      return this->string[index];
    }
    /// <summary>
    /// Get the first index occurrence of the specified character in the string.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the character wasn't found.</returns>
    Index indexOf(const String<T>& search, const Index from = 0) const {
      const auto length = search.getLength();
      if (length > 0) {
        auto begin = Math::Min(from, this->length);
        auto end = begin + length;
        while (end <= this->length) {
          if (this->compare(search, begin, end) == 0) {
            return begin;
          }
          begin++;
          end++;
        }
      }
      return -1;
    }
    /// <summary>
    /// Get the last index occurrence of the specified character in the string.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the character wasn't found.</returns>
    Index lastIndexOf(const String<T>& search, const Index from = -1) const {
      const auto length = search.getLength();
      if (length > 0) {
        auto begin = Math::Min(from, this->length);
        auto end = begin + length;
        if (end > this->length) {
          const auto overflow = (end - this->length);
          begin -= overflow;
          end -= overflow;
        }
        while (end >= length) {
          if (this->compare(search, begin, end) == 0) {
            return begin;
          }
          begin--;
          end--;
        }
      }
      return -1;
    }
    /// <summary>
    /// Compare the specified range with the given string.
    /// </summary>
    /// <param name="other">Other string.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>
    /// Returns -1 when this string is less than the other one.
    /// Returns  0 when this string is equals to the other one.
    /// Returns  1 when this string is greater than the other one.
    /// </returns>
    int compare(const String<T>& other, const Index from = 0, const Index to = -1) const {
      auto begin = Math::Min(from, this->length);
      const auto end = Math::Min(to, this->length);
      auto result = Compare(end - begin, other.getLength());
      for (Index index = 0; result == 0 && begin < end; ++begin, ++index) {
        result = Compare(this->string[begin], other[index]);
      }
      return result;
    }
    /// <summary>
    /// Slice a portion of the string based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the new string.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    BasicString slice(const Index from, const Index to = -1) const {
      if (from > to || from > this->length - 1) {
        throw Exceptions::IndexOutOfBounds(from);
      }
      return BasicString(&this->string[from], Math::Min(to, this->length) - from);
    }
    /// <summary>
    /// Reverse the string (in-place).
    /// </summary>
    void reverse() {
      using SPL::Swap;
      for (Size offset = 0; offset < this->length / 2; ++offset) {
        Swap(this->string[offset], this->string[this->length - 1 - offset]);
      }
    }
  public:
    /// <summary>
    /// Assign all properties from the given string.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    BasicString& operator = (BasicString other) noexcept {
      Swap(*this, other);
      return *this;
    }
    /// <summary>
    /// Get the array of characters.
    /// </summary>
    /// <returns>Returns the array of characters.</returns>
    operator const T* () const {
      return this->string;
    }
  };
}
