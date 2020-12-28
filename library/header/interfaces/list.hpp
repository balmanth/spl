/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"
#include "../pointers/unique.hpp"
#include "../metadata/constant.hpp"

namespace SPL {
  /// <summary>
  /// List interface.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class List {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~List() = default;
  public:
    /// <summary>
    /// Get the number of values in the list.
    /// </summary>
    /// <returns>Returns the list length.</returns>
    virtual Size getLength() const = 0;
    /// <summary>
    /// Determines whether or not the list is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    virtual bool isEmpty() const = 0;
    /// <summary>
    /// Add a copy of the specified value at the end of the list.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns the current length of the list.</returns>
    virtual Size add(const T& value) = 0;
    /// <summary>
    /// Add the specified value at the end of the list by using move semantics.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns the current length of the list.</returns>
    virtual Size add(Metadata::ConstantType<T>&& value) = 0;
    /// <summary>
    /// Add a copy of the specified value at the given index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Value.</param>
    /// <returns>Returns the current length of the list.</returns>
    virtual Size add(const Index index, const T& value) = 0;
    /// <summary>
    /// Add the specified value at the given index by using move semantics.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Value.</param>
    /// <returns>Returns the current length of the list.</returns>
    virtual Size add(const Index index, Metadata::ConstantType<T>&& value) = 0;
    /// <summary>
    /// Merge all the given lists into a new one.
    /// </summary>
    /// <param name="pack">Pack of lists.</param>
    /// <returns>Returns the new list.</returns>
    virtual Pointers::Unique<List<T>> concat(const Pack<List<T>>& pack) const = 0;
    /// <summary>
    /// Replace the value at the specified index with a copy of the given value.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Value.</param>
    /// <returns>Returns the replaced value.</returns>
    virtual T set(const Index index, const T& value) = 0;
    /// <summary>
    /// Replace the value at the specified index with the given value by using move semantics.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Value.</param>
    /// <returns>Returns the replaced value.</returns>
    virtual T set(const Index index, Metadata::ConstantType<T>&& value) = 0;
    /// <summary>
    /// Get the value that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual T& get(const Index index) const = 0;
    /// <summary>
    /// Get a copy of the value that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    virtual bool get(const Index index, Metadata::ConstantType<T>& value) const = 0;
    /// <summary>
    /// Get the first index occurrence of the specified value in the list.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 if the value wasn't found.</returns>
    virtual Index indexOf(const T& search, const Index from = 0) const = 0;
    /// <summary>
    /// Get the last index occurrence of the specified value in the list.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 if the value wasn't found.</returns>
    virtual Index lastIndexOf(const T& search, const Index from = -1) const = 0;
    /// <summary>
    /// Determines whether or not the list contains the specified value.
    /// </summary>
    /// <param name="search">Search value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    virtual bool contains(const T& search) const = 0;
    /// <summary>
    /// Remove the value that corresponds to the specified index from the list.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the removed value.</returns>
    virtual T remove(const Index index) = 0;
    /// <summary>
    /// Remove the value that corresponds to the specified index from the list.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    virtual bool remove(const Index index, Metadata::ConstantType<T>& value) = 0;
    /// <summary>
    /// Remove the first occurrence of the specified value from the list.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    virtual bool remove(Metadata::ConstantType<T>& value) = 0;
    /// <summary>
    /// Slice a portion of the list based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the generated list.</returns>
    virtual Pointers::Unique<List<T>> slice(const Index from, const Index to = -1) const = 0;
    // <summary>
    /// Sort the list.
    /// </summary>
    virtual void sort() = 0;
    // <summary>
    /// Reverse the list.
    /// </summary>
    virtual void reverse() = 0;
    /// <summary>
    /// Clear the list.
    /// </summary>
    virtual void clear() = 0;
  public:
    /// <summary>
    /// Get the value that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual const T& operator [](const Index index) const = 0;
    /// <summary>
    /// Get the value that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual T& operator [](const Index index) = 0;
  };
}
