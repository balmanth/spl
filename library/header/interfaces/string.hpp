/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"
#include "../pointers/unique.hpp"
#include "./comparable.hpp"

namespace SPL {
  /// <summary>
  /// String interface.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class String : public Comparable<String<T>> {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~String() = default;
  public:
    /// <summary>
    /// Get the number of characters in the string.
    /// </summary>
    /// <returns>Returns the string length.</returns>
    virtual Size getLength() const = 0;
    /// <summary>
    /// Determines whether or not the string is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    virtual bool isEmpty() const = 0;
    /// <summary>
    /// Merge all the given strings into a new one.
    /// </summary>
    /// <param name="pack">Pack of strings.</param>
    /// <returns>Returns the new string.</returns>
    virtual Pointers::Unique<String<T>> concat(const Pack<String<T>>& pack) const = 0;
    /// <summary>
    /// Get the first index occurrence of the specified value in the string.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 if the value wasn't found.</returns>
    virtual Index indexOf(const String<T>& search, const Index from = 0) const = 0;
    /// <summary>
    /// Get the last index occurrence of the specified value in the string.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 if the value wasn't found.</returns>
    virtual Index lastIndexOf(const String<T>& search, const Index from = -1) const = 0;
    /// <summary>
    /// Determines whether or not the string contains the specified value.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    virtual bool contains(const String<T>& search) const = 0;
    /// <summary>
    /// Determines whether or not the string starts with the specified value.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <returns>Returns true when the string starts with the specified value, false otherwise.</returns>
    virtual bool startsWith(const String<T>& search) const = 0;
    /// <summary>
    /// Determines whether or not the string ends with the specified value.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <returns>Returns true when the string ends with the specified value, false otherwise.</returns>
    virtual bool endsWith(const String<T>& search) const = 0;
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
    virtual int compare(const String<T>& other, const Index from = 0, const Index to = -1) const = 0;
    /// <summary>
    /// Slice a portion of the string based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the new string.</returns>
    virtual Pointers::Unique<String<T>> slice(const Index from, const Index to = -1) const = 0;
    // <summary>
    /// Reverse the string.
    /// </summary>
    virtual void reverse() = 0;
  public:
    /// <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    virtual const T& operator [](const Index index) const = 0;
    /// <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    virtual T& operator [](const Index index) = 0;
  };
}
