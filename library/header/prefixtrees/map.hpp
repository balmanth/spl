/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./base.hpp"

namespace SPL::PrefixTrees {
  /// <summary>
  /// Prefix Map class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  class Map final : public SPL::Map<K, V> {
  private:
    /// <summary>
    /// Base tree.
    /// </summary>
    Base<K, V> tree;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="values">Initial values.</param>
    template<Size N>
    Map(const Pair<K, V>(&pairs)[N]) : Map() {
      for (const Pair<K, V>& pair : pairs) {
        this->set(pair.key, pair.value);
      }
    }
    /// <summary>
    /// Default constructor.
    /// </summary>
    Map() :
      tree() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Map(const Map<K, V>& other) :
      tree(other.tree) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Map(Map<K, V>&& other) noexcept :
      tree(Move(other.tree)) {}
  public:
    /// <summary>
    /// Get the number of prefixes in the map.
    /// </summary>
    /// <returns>Returns the map size.</returns>
    Size getSize() const override {
      return this->tree.getSize();
    }
    /// <summary>
    /// Determines whether or not the map is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    bool isEmpty() const override {
      return this->tree.getSize() == 0;
    }
    /// <summary>
    /// Set the specified key to map the given value by using move semantics.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <param name="value">Prefix value.</param>
    /// <returns>Returns the previous value in the given key.</returns>
    /// <exception cref="SPL::Exceptions::InvalidArgument">Throws when the specified key is empty.</exception>
    V set(const K& key, Metadata::ConstantType<V>&& value) override {
      Node<K, V>* node = this->tree.set(key);
      if (node == nullptr) {
        throw Exceptions::InvalidArgument();
      }
      using SPL::Swap;
      V previous(Move(node->value));
      Swap(node->value, value);
      return previous;
    }
    /// <summary>
    /// Set a copy of the specified key to map the given value.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <param name="value">Prefix value.</param>
    /// <returns>Returns the previous value in the given key.</returns>
    /// <exception cref="SPL::Exceptions::InvalidArgument">Throws when the specified key is empty.</exception>
    V set(const K& key, const V& value) override {
      Metadata::ConstantType<V> copy(value);
      return this->set(key, Move(copy));
    }
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <returns>Returns the corresponding prefix value.</returns>
    /// <exception cref="SPL::Exceptions::KeyNotFound">Throws when the specified key doesn't exists.</exception>
    V& get(const K& key) const override {
      Node<K, V>* node = this->tree.get(key);
      if (node == nullptr) {
        throw Exceptions::KeyNotFound<K>(key);
      }
      return node->value;
    }
    /// <summary>
    /// Get a copy of the value that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    bool get(const K& key, Metadata::ConstantType<V>& value) const override {
      Node<K, V>* node = this->tree.get(key);
      if (node != nullptr) {
        value = node->value;
        return true;
      }
      return false;
    }
    /// <summary>
    /// Determines whether or not the map contains the specified key.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <returns>Returns true when the key was found, false otherwise.</returns>
    bool has(const K& key) const override {
      return this->tree.get(key) != nullptr;
    }
    /// <summary>
    /// Remove the specified key from the map.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <returns>Returns the removed value.</returns>
    /// <exception cref="SPL::Exceptions::KeyNotFound">Throws when the specified key doesn't exists.</exception>
    V remove(const K& key) override {
      Node<K, V>* node = this->tree.unset(key);
      if (node == nullptr) {
        throw Exceptions::KeyNotFound<K>(key);
      }
      V previous(Move(node->value));
      return previous;
    }
    /// <summary>
    /// Remove the specified key from the map.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <param name="value">Output value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    bool remove(const K& key, Metadata::ConstantType<V>& value) override {
      Node<K, V>* node = this->tree.unset(key);
      if (node != nullptr) {
        value = node->value;
        return true;
      }
      return false;
    }
    /// <summary>
    /// Clear the map.
    /// </summary>
    void clear() override {
      this->tree.clear();
    }
  public:
    /// <summary>
    /// Alias for the get method.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <returns>Returns the corresponding prefix value.</returns>
    const V& operator [](const K& key) const override {
      return this->get(key);
    }
    /// <summary>
    /// Get the value that corresponds to the specified key.
    /// It creates a new prefix when the given key doesn't exists.
    /// </summary>
    /// <param name="key">Prefix key.</param>
    /// <returns>Returns the corresponding prefix value.</returns>
    V& operator [](const K& key) override {
      Node<K, V>* node = this->tree.set(key);
      return node->value;
    }
    /// <summary>
    /// Assign all properties from the given map.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Map<K, V>& operator = (Map<K, V> other) noexcept {
      this->tree = Move(other.tree);
      return *this;
    }
    /// <summary>
    /// Get the root node.
    /// </summary>
    /// <returns>Returns the root node.</returns>
    operator const Node<K, V>* () const {
      return static_cast<const Node<K, V>*>(this->tree);
    }
  };
}
