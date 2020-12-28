/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./entry_iterator.hpp"
#include "./basic_table.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Hash map class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  /// <typeparam name="H">Hash function.</typeparam>
  template<typename K, typename V, Id(H)(const K&)>
  class HashMap final : public Map<K, V>, public Iterable<HashEntry<K, V>> {
  private:
    /// <summary>
    /// Hash entry type.
    /// </summary>
    using EntryType = HashEntry<K, V>;
    /// <summary>
    /// Non-constant value type.
    /// </summary>
    using ValueType = Metadata::ConstantType<V>;
    /// <summary>
    /// Base table.
    /// </summary>
    BasicTable<H, K, V> table;
  private:
    /// <summary>
    /// Enlarge the current capacity.
    /// </summary>
    void enlarge() {
      if (this->getLoadFactor() >= 0.7f) {
        this->table.enlarge(this->getCapacity() << 1);
      }
    }
    /// <summary>
    /// Shrink the current capacity.
    /// </summary>
    void shrink() {
      if (this->getLoadFactor() <= 0.3f) {
        this->table.shrink(this->getCapacity() >> 1);
      }
    }
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="capacity">Initial capacity.</param>
    explicit HashMap(const Size capacity) :
      table(NP2(capacity)) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="values">Initial values.</param>
    template<Size N>
    HashMap(const Pair<K, V>(&pairs)[N]) : HashMap(N) {
      for (const auto& pair : pairs) {
        this->set(pair.key, pair.value);
      }
    }
    /// <summary>
    /// Default constructor.
    /// </summary>
    HashMap() :
      table() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashMap(const HashMap& other) :
      table(other.table) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashMap(HashMap&& other) noexcept :
      table(Move(other.table)) {}
  public:
    /// <summary>
    /// Get the hash map capacity.
    /// </summary>
    /// <returns>Returns the hash map capacity.</returns>
    Size getCapacity() const {
      return this->table.getCapacity();
    }
    /// <summary>
    /// Get the load factor (between 0.0f and 1.0f).
    /// </summary>
    /// <returns>Returns the load factor.</returns>
    float getLoadFactor() const {
      return Math::Min((static_cast<float>(this->getSize()) / this->getCapacity()), 1.0f);
    }
    /// <summary>
    /// Get the number of entries in the hash map.
    /// </summary>
    /// <returns>Returns the map size.</returns>
    Size getSize() const override {
      return this->table.getSize();
    }
    /// <summary>
    /// Determines whether or not the hash map is empty.
    /// </summary>
    /// <returns>Returns true when the it's empty, false otherwise.</returns>
    bool isEmpty() const override {
      return this->table.getSize() == 0;
    }
    /// <summary>
    /// Get a new entry iterator.
    /// </summary>
    /// <returns>Returns the new iterator.</returns>
    UniqueIterator<EntryType> getIterator() const override {
      auto* iterator = new EntryIterator<H, K, V>(this->table);
      return UniqueIterator<EntryType>(iterator);
    }
    /// <summary>
    /// Set the specified key to map the given value by using move semantics.
    /// When the load factor is greater than or equals to 0.7f the current capacity will double.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <param name="value">Entry value.</param>
    /// <returns>Returns the previous value for the given key.</returns>
    V set(const K& key, ValueType&& value) override {
      this->enlarge();
      auto* entry = this->table.set(key);
      V previous(Move(entry->value));
      using SPL::Swap;
      Swap(entry->value, value);
      return previous;
    }
    /// <summary>
    /// Set the specified key using the given value.
    /// When the load factor is greater than or equals to 0.7f the current capacity will double.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <param name="value">Entry value.</param>
    /// <returns>Returns the previous value for the given key.</returns>
    V set(const K& key, const ValueType& value) override {
      ValueType copy(value);
      return this->set(key, Move(copy));
    }
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns the corresponding entry value.</returns>
    /// <exception cref="SPL::Exceptions::KeyNotFound">Throws when the specified key doesn't exists.</exception>
    V& get(const K& key) const override {
      auto* entry = this->table.get(key);
      if (entry == nullptr) {
        throw Exceptions::KeyNotFound<K>(key);
      }
      return entry->value;
    }
    /// <summary>
    /// Get a copy of the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    bool get(const K& key, ValueType& value) const override {
      auto* entry = this->table.get(key);
      if (entry != nullptr) {
        value = entry->value;
        return true;
      }
      return false;
    }
    /// <summary>
    /// Determines whether or not the hash map contains the specified key.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns true when the key was found, false otherwise.</returns>
    bool has(const K& key) const override {
      return this->table.get(key) != nullptr;
    }
    /// <summary>
    /// Remove the specified key from the hash map.
    /// When the load factor is less than or equals to 0.3f the map capacity will reduce by half.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns the removed value.</returns>
    /// <exception cref="SPL::Exceptions::KeyNotFound">Throws when the specified key doesn't exists.</exception>
    V remove(const K& key) override {
      auto* entry = this->table.unset(key);
      if (entry == nullptr) {
        throw Exceptions::KeyNotFound<K>(key);
      }
      V previous(Move(entry->value));
      this->shrink();
      return previous;
    }
    /// <summary>
    /// Remove the specified key from the hash map.
    /// When the load factor is less than or equals to 0.3f the map capacity will reduce by half.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    bool remove(const K& key, ValueType& value) override {
      auto* entry = this->table.unset(key);
      if (entry != nullptr) {
        value = entry->value;
        this->shrink();
        return true;
      }
      return false;
    }
    /// <summary>
    /// Clear the hash map.
    /// The current capacity will remains the same.
    /// </summary>
    void clear() override {
      this->table.clear();
    }
  public:
    /// <summary>
    /// Alias for the get method.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns the corresponding entry value.</returns>
    const V& operator [](const K& key) const override {
      return this->get(key);
    }
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// It creates a new entry when the given key doesn't exists.
    /// When the load factor is greater than or equals to 0.7f the map capacity will double.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns the corresponding entry value.</returns>
    V& operator [](const K& key) override {
      this->enlarge();
      auto* entry = this->table.set(key);
      return entry->value;
    }
    /// <summary>
    /// Assign all properties from the given hash map.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    HashMap& operator = (HashMap other) noexcept {
      this->table = Move(other.table);
      return *this;
    }
    /// <summary>
    /// Get the array of entries.
    /// </summary>
    /// <returns>Returns the array of entries.</returns>
    operator const EntryType* () const {
      return static_cast<const EntryType*>(this->table);
    }
  };
}
