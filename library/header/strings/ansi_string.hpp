/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./string_iterator.hpp"
#include "./basic_string.hpp"

namespace SPL::Strings {
  /// <summary>
  /// ANSI string class.
  /// </summary>
  class AnsiString final : public String<char>, public Iterable<char> {
  private:
    /// <summary>
    /// Basic string type.
    /// </summary>
    using BasicType = BasicString<char>;
    /// <summary>
    /// Basic string.
    /// </summary>
    BasicType string;
  private:
    /// <summary>
    /// Internal constructor.
    /// </summary>
    /// <param name="string">Initial string.</param>
    explicit AnsiString(BasicType& string) : AnsiString() {
      using SPL::Swap;
      Swap(this->string, string);
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    AnsiString() :
      string() {}
    /// <summary>
    /// Initialized constructor for length.
    /// </summary>
    /// <param name="length">Initial length.</param>
    AnsiString(const Size length) :
      string(length) {}
    /// <summary>
    /// Initialized constructor for pointer and length.
    /// </summary>
    /// <param name="string">Initial string.</param>
    /// <param name="length">Initial length.</param>
    AnsiString(const char string[], const Size length) :
      string(string, length) {}
    /// <summary>
    /// Initialized constructor for string.
    /// </summary>
    /// <param name="string">Initial string.</param>
    template<Size N>
    AnsiString(const char(&string)[N]) :
      string(string) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    AnsiString(const AnsiString& other) :
      string(other.string) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    AnsiString(AnsiString&& other) noexcept :
      string(Move(other.string)) {}
  public:
    /// <summary>
    /// Get the number of characters in the string.
    /// </summary>
    /// <returns>Returns the string length.</returns>
    Size getLength() const override {
      return this->string.getLength();
    }
    /// <summary>
    /// Determines whether or not the string is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    bool isEmpty() const override {
      return this->string.getLength() == 0;
    }
    /// <summary>
    /// Get a new string iterator.
    /// </summary>
    /// <returns>Returns the new iterator.</returns>
    UniqueIterator<char> getIterator() const override {
      auto* iterator = new StringIterator<char>(this->string);
      return UniqueIterator<char>(iterator);
    }
    /// <summary>
    /// Merge all the given strings into a new one.
    /// </summary>
    /// <param name="pack">Pack of strings.</param>
    /// <returns>Returns the new string.</returns>
    UniqueString<char> concat(const StringPack<char>& pack) const override {
      auto string = this->string.concat(pack);
      return UniqueString<char>(new AnsiString(string));
    }
    /// <summary>
    /// Get the first index occurrence of the specified character in the string.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the character wasn't found.</returns>
    Index indexOf(const String<char>& search, const Index from = 0) const override {
      return this->string.indexOf(search, from);
    }
    /// <summary>
    /// Get the last index occurrence of the specified character in the string.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the character wasn't found.</returns>
    Index lastIndexOf(const String<char>& search, const Index from = -1) const override {
      return this->string.lastIndexOf(search, from);
    }
    /// <summary>
    /// Determines whether or not the string contains the specified character.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <returns>Returns true when the character was found, false otherwise.</returns>
    bool contains(const String<char>& search) const override {
      return this->string.indexOf(search) != -1;
    }
    /// <summary>
    /// Determines whether or not the string starts with the specified character.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <returns>Returns true when the string starts with the specified character, false otherwise.</returns>
    bool startsWith(const String<char>& search) const override {
      return this->string.compare(search, 0, search.getLength()) == 0;
    }
    /// <summary>
    /// Determines whether or not the string ends with the specified character.
    /// </summary>
    /// <param name="search">Search character.</param>
    /// <returns>Returns true when the string ends with the specified character, false otherwise.</returns>
    bool endsWith(const String<char>& search) const override {
      return this->string.compare(search, this->string.getLength() - search.getLength()) == 0;
    }
    /// <summary>
    /// Compare both strings.
    /// </summary>
    /// <param name="other">Other string.</param>
    /// <returns>
    /// Returns -1 when this string is less than the other one.
    /// Returns  0 when this string is equals to the other one.
    /// Returns  1 when this string is greater than the other one.
    /// </returns>
    int compare(const String<char>& other) const override {
      return this->string.compare(other);
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
    int compare(const String<char>& other, const Index from, const Index to = -1) const override {
      return this->string.compare(other, from, to);
    }
    /// <summary>
    /// Slice a portion of the string based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the new string.</returns>
    /// <exception cref="SPL::IndexOutOfBoundsException">Throws when the specified index is out of bounds.</exception>
    UniqueString<char> slice(const Index from, const Index to = -1) const override {
      auto string = this->string.slice(from, to);
      return UniqueString<char>(new AnsiString(string));
    }
    /// <summary>
    /// Reverse the string (in-place).
    /// </summary>
    void reverse() override {
      this->string.reverse();
    }
  public:
    /// <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    const char& operator [](const Index index) const override {
      return this->string.get(index);
    }
    /// <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    char& operator [](const Index index) override {
      return this->string.get(index);
    }
    /// <summary>
    /// Assign all properties from the given string.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    AnsiString& operator = (AnsiString other) noexcept {
      this->string = Move(other.string);
      return *this;
    }
  };
}
