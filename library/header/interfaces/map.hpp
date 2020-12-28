/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"
#include "../metadata/constant.hpp"

namespace SPL {
  /// <summary>
  /// Map interface.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  class Map {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Map() = default;
  public:
    /// <summary>
    /// Get the number of values in the map.
    /// </summary>
    /// <returns>Returns the map size.</returns>
    virtual Size getSize() const = 0;
    /// <summary>
    /// Determines whether or not the map is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    virtual bool isEmpty() const = 0;
    /// <summary>
    /// Set the specified key to map the given value by using move semantics.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <param name="value">Entry value.</param>
    /// <returns>Returns the previous value in the given key.</returns>
    virtual V set(const K& key, Metadata::ConstantType<V>&& value) = 0;
    /// <summary>
    /// Set the specified key to map a copy of the given value.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <param name="value">Entry value.</param>
    /// <returns>Returns the previous value in the given key.</returns>
    virtual V set(const K& key, const V& value) = 0;
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual V& get(const K& key) const = 0;
    /// <summary>
    /// Get a copy of the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    virtual bool get(const K& key, Metadata::ConstantType<V>& value) const = 0;
    /// <summary>
    /// Determines whether or not the map contains the specified key.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <returns>Returns true when the key was found, false otherwise.</returns>
    virtual bool has(const K& key) const = 0;
    /// <summary>
    /// Remove the specified key from the map.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <returns>Returns the removed value.</returns>
    virtual V remove(const K& key) = 0;
    /// <summary>
    /// Remove the specified key from the map.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    virtual bool remove(const K& key, Metadata::ConstantType<V>& value) = 0;
    /// <summary>
    /// Clear the map.
    /// </summary>
    virtual void clear() = 0;
  public:
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual const V& operator [](const K& key) const = 0;
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// It creates a new entry when the given key doesn't exists.
    /// </summary>
    /// <param name="key">Key.</param>
    /// <returns>Returns the corresponding value.</returns>
    virtual V& operator [](const K& key) = 0;
  };
}
