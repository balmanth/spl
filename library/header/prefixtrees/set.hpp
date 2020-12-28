/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./base.hpp"

namespace SPL::PrefixTrees {
  /// <summary>
  /// Prefix Set class.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  template<typename T>
  class Set final : public SPL::Set<T> {
  private:
    /// <summary>
    /// Base tree.
    /// </summary>
    Base<T> tree;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="values">Initial values.</param>
    template<Size N>
    Set(const T(&values)[N]) : Set() {
      for (const T& value : values) {
        this->add(value);
      }
    }
    /// <summary>
    /// Default constructor.
    /// </summary>
    Set() :
      tree() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Set(const Set<T>& other) :
      tree(other.tree) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Set(Set<T>&& other) noexcept :
      tree(Move(other.tree)) {}
  public:
    /// <summary>
    /// Get the number of prefixes in the set.
    /// </summary>
    /// <returns>Returns the set size.</returns>
    Size getSize() const override {
      return this->tree.getSize();
    }
    /// <summary>
    /// Determines whether or not the set is empty.
    /// </summary>
    /// <returns>Returns true when the it's empty, false otherwise.</returns>
    bool isEmpty() const override {
      return this->tree.getSize() == 0;
    }
    /// <summary>
    /// Add the specified value in the set by using move semantics.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <exception cref="SPL::Exceptions::InvalidArgument">Throws when the specified key is empty.</exception>
    void add(Metadata::ConstantType<T>&& value) override {
      Node<T>* node = this->tree.set(Forward<Metadata::ConstantType<T>>(value));
      if (node == nullptr) {
        throw Exceptions::InvalidArgument();
      }
    }
    /// <summary>
    /// Add a copy of the specified value in the set.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <exception cref="SPL::Exceptions::InvalidArgument">Throws when the specified key is empty.</exception>
    void add(const T& value) override {
      Metadata::ConstantType<T> copy(value);
      this->add(Move(copy));
    }
    /// <summary>
    /// Determines whether or not the set contains the specified value.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    bool has(const T& value) const override {
      return this->tree.get(value) != nullptr;
    }
    /// <summary>
    /// Remove the specified value from the set.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    bool remove(const T& value) override {
      Node<T>* node = this->tree.unset(value);
      return node != nullptr;
    }
    /// <summary>
    /// Clear the set.
    /// The current capacity will remains the same.
    /// </summary>
    void clear() override {
      this->tree.clear();
    }
  public:
    /// <summary>
    /// Assign all properties from the given set.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Set<T>& operator = (Set<T> other) noexcept {
      this->tree = Move(other.tree);
      return *this;
    }
    /// <summary>
    /// Get the root node.
    /// </summary>
    /// <returns>Returns the root node.</returns>
    operator const Node<T>* () const {
      return static_cast<const Node<T>*>(this->tree);
    }
  };
}
