/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Hash entry class only for keys.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  template<typename K>
  class HashEntry<K> {
    // Friend class.
    template<auto, typename, typename ...> friend class BasicTable;
  private:
    /// <summary>
    /// Non-constant key type.
    /// </summary>
    using KeyType = Metadata::ConstantType<K>;
    /// <summary>
    /// Entry hash.
    /// </summary>
    Id hash;
    /// <summary>
    /// Entry state.
    /// </summary>
    EntryState state;
    /// <summary>
    /// Entry key.
    /// </summary>
    KeyType key;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(HashEntry& source, HashEntry& target) noexcept {
      using SPL::Swap;
      Swap(source.hash, target.hash);
      Swap(source.state, target.state);
      Swap(source.key, target.key);
    }
  protected:
    /// <summary>
    /// Default constructor.
    /// </summary>
    HashEntry() :
      hash(-1), state(EntryState::Free), key() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashEntry(const HashEntry& other) :
      hash(other.hash), state(other.state), key(other.key) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashEntry(HashEntry&& other) noexcept : HashEntry() {
      Swap(*this, other);
    }
  public:
    /// <summary>
    /// Get the entry hash.
    /// </summary>
    /// <returns>Returns the entry hash.</returns>
    Id getHash() const {
      return this->hash;
    }
    /// <summary>
    /// Get the entry state.
    /// </summary>
    /// <returns>Returns the entry state.</returns>
    EntryState getState() const {
      return this->state;
    }
    /// <summary>
    /// Get the entry key.
    /// </summary>
    /// <returns>Returns the entry key.</returns>
    const K& getKey() const {
      return this->key;
    }
  public:
    /// <summary>
    /// Assign all properties from the given entry.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    HashEntry& operator = (HashEntry other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
  /// <summary>
  /// Hash entry class for keys and values.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  class HashEntry<K, V> : public HashEntry<K> {
    // Friend class.
    template<auto, typename, typename ...> friend class BasicTable;
  public:
    /// <summary>
    /// Base entry type.
    /// </summary>
    using BaseType = HashEntry<K>;
    /// <summary>
    /// Entry value.
    /// </summary>
    V value;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(HashEntry& source, HashEntry& target) noexcept {
      using SPL::Swap;
      Swap(static_cast<BaseType&>(source), static_cast<BaseType&>(target));
      Swap(source.value, target.value);
    }
  protected:
    /// <summary>
    /// Default constructor.
    /// </summary>
    HashEntry() :
      value(), BaseType() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashEntry(const HashEntry& other) :
      value(other.value), BaseType(other) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashEntry(HashEntry&& other) noexcept : HashEntry() {
      Swap(*this, other);
    }
  public:
    /// <summary>
    /// Assign all properties from the given entry.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    HashEntry& operator = (HashEntry other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
}
