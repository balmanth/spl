/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./node.hpp"

namespace SPL::PrefixTrees {
  /// <summary>
  /// Base tree class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="...V">Value type.</typeparam>
  template<typename K, typename ...V>
  class Base final {
  private:
    /// <summary>
    /// Root node.
    /// </summary>
    Node<K, V...>* root;
    /// <summary>
    /// Current number of prefixes.
    /// </summary>
    Size size;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Base<K, V...>& source, Base<K, V...>& target) noexcept {
      using SPL::Swap;
      Swap(source.root, target.root);
      Swap(source.size, target.size);
    }
    /// <summary>
    /// Load the node that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Node key.</param>
    /// <returns>Returns the reference for the corresponding node or null when it wasn't found.</returns>
    Node<K, V...>* load(const K& key) const {
      Node<K, V...>* current = this->root;
      Node<K, V...>* previous = nullptr;
      Index index = 0;
      while (key[index] != Metadata::PointerType<K>()) {
        if (current == nullptr) {
          return nullptr;
        }
        int comparison = Compare(current->key, key[index]);
        if (comparison < 0) {
          current = current->left;
        }
        else if (comparison > 0) {
          current = current->right;
        }
        else {
          previous = current;
          current = current->down;
          index++;
        }
      }
      return previous;
    }
    /// <summary>
    /// Append new nodes based on the given key.
    /// </summary>
    /// <param name="key">Node key.</param>
    /// <returns>Returns the reference for the last inserted node.</returns>
    Node<K, V...>*& append(const K& key) {
      Node<K, V...>** current = &this->root;
      Node<K, V...>** previous = current;
      for (Size offset = 0; key[offset] != Metadata::PointerType<K>();) {
        if (*current != nullptr) {
          int comparison = Compare((*current)->key, key[offset]);
          if (comparison < 0) {
            current = &(*current)->left;
            continue;
          }
          else if (comparison > 0) {
            current = &(*current)->right;
            continue;
          }
        }
        else {
          *current = new Node<K, V...>(key[offset]);
        }
        previous = current;
        current = &(*current)->down;
        offset++;
      }
      return *previous;
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Base() :
      root(nullptr), size(0) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Base(const Base<K, V...>& other) :
      root(other.root != nullptr ? new Node<K, V...>(*other.root) : nullptr), size(other.size) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Base(Base<K, V...>&& other) noexcept : Base() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Base() {
      delete this->root;
    }
  public:
    /// <summary>
    /// Get the number of prefixes in the tree.
    /// </summary>
    /// <returns>Returns the tree size.</returns>
    Size getSize() const {
      return this->size;
    }
    /// <summary>
    /// Set a terminal prefix node for the specified key.
    /// If it doesn't exists try to create a new one.
    /// </summary>
    /// <param name="key">Node key.</param>
    /// <returns>Returns a pointer to the corresponding node or null when isn't possible to set it.</returns>
    Node<K, V...>* set(const K& key) {
      if (key != nullptr) {
        Node<K, V...>* node = this->load(key);
        if (node == nullptr || !node->terminal) {
          node = this->append(key);
          node->terminal = true;
          this->size++;
        }
        return node;
      }
      return nullptr;
    }
    /// <summary>
    /// Get the terminal prefix node that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Node key.</param>
    /// <returns>Returns a pointer to the corresponding node or null when isn't possible to get it.</returns>
    Node<K, V...>* get(const K& key) const {
      if (key != nullptr) {
        Node<K, V...>* node = this->load(key);
        if (node != nullptr && node->terminal) {
          return node;
        }
      }
      return nullptr;
    }
    /// <summary>
    /// Unset the terminal prefix node that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Node key.</param>
    /// <returns>Returns a pointer to the corresponding node or null when isn't possible to unset it.</returns>
    Node<K, V...>* unset(const K& key) {
      if (key != nullptr) {
        Node<K, V...>* node = this->load(key);
        if (node != nullptr && node->terminal) {
          node->terminal = false;
          this->size--;
          return node;
        }
      }
      return nullptr;
    }
    /// <summary>
    /// Clear the tree.
    /// </summary>
    void clear() {
      delete this->root;
      this->root = nullptr;
      this->size = 0;
    }
  public:
    /// <summary>
    /// Assign all properties from the given tree.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Base<K, V...>& operator = (Base<K, V...> other) noexcept {
      Swap(*this, other);
      return *this;
    }
    /// <summary>
    /// Get the root node.
    /// </summary>
    /// <returns>Returns the root node.</returns>
    operator const Node<K, V...>* () const {
      return this->root;
    }
  };
}
