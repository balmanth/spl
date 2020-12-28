/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::PrefixTrees {
  /// <summary>
  /// Key node class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  template<typename K>
  class Node<K> final {
    // Friend base class.
    template<typename, typename ...> friend class Base;
  private:
    /// <summary>
    /// Left key node.
    /// </summary>
    Node<K>* left;
    /// <summary>
    /// Right key node.
    /// </summary>
    Node<K>* right;
    /// <summary>
    /// Down key node.
    /// </summary>
    Node<K>* down;
    /// <summary>
    /// Determines whether or not the node is terminal.
    /// </summary>
    bool terminal;
    /// <summary>
    /// Entry key.
    /// </summary>
    Metadata::PointerType<K> key;
  private:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    explicit Node(const Metadata::PointerType<K>& key) :
      left(nullptr), right(nullptr), down(nullptr), terminal(false), key(key) {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    Node() :
      left(nullptr), right(nullptr), down(nullptr), terminal(false), key() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Node(const Node<K>& other) :
      left(nullptr), right(nullptr), down(nullptr), terminal(other.terminal), key(other.key) {
      if (other.left != nullptr) {
        this->left = new Node<K>(*other.left);
      }
      if (other.right != nullptr) {
        this->right = new Node<K>(*other.right);
      }
      if (other.down != nullptr) {
        this->down = new Node<K>(*other.down);
      }
    }
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Node(Node<K>&& other) noexcept : Node() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Node() {
      delete this->left;
      delete this->right;
      delete this->down;
    }
  protected:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Node<K>& source, Node<K>& target) noexcept {
      using SPL::Swap;
      Swap(source.left, target.left);
      Swap(source.right, target.right);
      Swap(source.down, target.down);
      Swap(source.terminal, target.terminal);
      Swap(source.key, target.key);
    }
  public:
    /// <summary>
    /// Determines whether or not the node is terminal.
    /// </summary>
    /// <returns>Returns true when it's terminal, false otherwise.</returns>
    bool isTerminal() const {
      return this->terminal;
    }
    /// <summary>
    /// Get the node key.
    /// </summary>
    /// <returns>Returns the node key.</returns>
    const Metadata::PointerType<K>& getKey() const {
      return this->key;
    }
    /// <summary>
    /// Get the left node.
    /// </summary>
    /// <returns>Returns the left node.</returns>
    const Node<K>* getLeftNode() const {
      return this->left;
    }
    /// <summary>
    /// Get the right node.
    /// </summary>
    /// <returns>Returns the right node.</returns>
    const Node<K>* getRightNode() const {
      return this->right;
    }
    /// <summary>
    /// Get the down node.
    /// </summary>
    /// <returns>Returns the down node.</returns>
    const Node<K>* getDownNode() const {
      return this->down;
    }
  };
  /// <summary>
  /// Key/Value node class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="V">Value type.</typeparam>
  template<typename K, typename V>
  class Node<K, V> final {
    // Friend base class.
    template<typename, typename ...> friend class Base;
  private:
    /// <summary>
    /// Left key node.
    /// </summary>
    Node<K, V>* left;
    /// <summary>
    /// Right key node.
    /// </summary>
    Node<K, V>* right;
    /// <summary>
    /// Down key node.
    /// </summary>
    Node<K, V>* down;
    /// <summary>
    /// Determines whether or not the node is terminal.
    /// </summary>
    bool terminal;
    /// <summary>
    /// Entry key.
    /// </summary>
    Metadata::PointerType<K> key;
  public:
    /// <summary>
    /// Node value.
    /// </summary>
    V value;
  private:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    explicit Node(const Metadata::PointerType<K>& key) :
      left(nullptr), right(nullptr), down(nullptr), terminal(false), key(key), value() {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    Node() :
      left(nullptr), right(nullptr), down(nullptr), terminal(false), key(), value() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Node(const Node<K, V>& other) :
      left(nullptr), right(nullptr), down(nullptr), terminal(other.terminal), key(other.key), value(other.value) {
      if (other.left != nullptr) {
        this->left = new Node<K, V>(*other.left);
      }
      if (other.right != nullptr) {
        this->right = new Node<K, V>(*other.right);
      }
      if (other.down != nullptr) {
        this->down = new Node<K, V>(*other.down);
      }
    }
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Node(Node<K, V>&& other) noexcept : Node() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Node() {
      delete this->left;
      delete this->right;
      delete this->down;
    }
  protected:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Node<K, V>& source, Node<K, V>& target) noexcept {
      using SPL::Swap;
      Swap(source.left, target.left);
      Swap(source.right, target.right);
      Swap(source.down, target.down);
      Swap(source.terminal, target.terminal);
      Swap(source.key, target.key);
      Swap(source.value, target.value);
    }
  public:
    /// <summary>
    /// Determines whether or not the node is terminal.
    /// </summary>
    /// <returns>Returns true when it's terminal, false otherwise.</returns>
    bool isTerminal() const {
      return this->terminal;
    }
    /// <summary>
    /// Get the node key.
    /// </summary>
    /// <returns>Returns the node key.</returns>
    const Metadata::PointerType<K>& getKey() const {
      return this->key;
    }
    /// <summary>
    /// Get the left node.
    /// </summary>
    /// <returns>Returns the left node.</returns>
    const Node<K, V>* getLeftNode() const {
      return this->left;
    }
    /// <summary>
    /// Get the right node.
    /// </summary>
    /// <returns>Returns the right node.</returns>
    const Node<K, V>* getRightNode() const {
      return this->right;
    }
    /// <summary>
    /// Get the down node.
    /// </summary>
    /// <returns>Returns the down node.</returns>
    const Node<K, V>* getDownNode() const {
      return this->down;
    }
  };
}
