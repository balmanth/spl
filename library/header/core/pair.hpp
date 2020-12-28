/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./swap.hpp"

namespace SPL {
  /// <summary>
  /// Pair class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  class Pair final {
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Pair<K, V>& source, Pair<K, V>& target) noexcept {
      using SPL::Swap;
      Swap(source.key, target.key);
      Swap(source.value, target.value);
    }
  public:
    /// <summary>
    /// Key.
    /// </summary>
    K key;
    /// <summary>
    /// Value.
    /// </summary>
    V value;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Pair() :
      key(), value() {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="key">Initial key.</param>
    /// <param name="value">Initial value.</param>
    Pair(const K& key, const V& value) :
      key(key), value(value) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Pair(const Pair<K, V>& other) :
      key(other.key), value(other.value) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Pair(Pair<K, V>&& other) noexcept : Pair() {
      Swap(*this, other);
    }
  public:
    /// <summary>
    /// Check whether or not the given pairs are equals.
    /// </summary>
    /// <param name="pair">Other instance.</param>
    /// <returns>Returns true when both are equals, false otherwise.</returns>
    bool operator == (const Pair<K, V>& pair) const {
      return Compare(this->key, pair.key) == 0 && Compare(this->value, pair.value) == 0;
    }
    /// <summary>
    /// Assign all properties from the given pair.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Pair<K, V>& operator = (Pair<K, V> other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
}
