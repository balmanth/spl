/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./entry_iterator.hpp"
#include "./basic_table.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Hash set class.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="H">Hash function.</typeparam>
  template<typename T, Id(H)(const T&)>
  class HashSet final : public Set<T>, public Iterable<HashEntry<T>> {
  private:
    /// <summary>
    /// Hash entry type.
    /// </summary>
    using EntryType = HashEntry<T>;
    /// <summary>
    /// Non-constant value type.
    /// </summary>
    using ValueType = Metadata::ConstantType<T>;
    /// <summary>
    /// Base table.
    /// </summary>
    BasicTable<H, T> table;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="capacity">Initial capacity.</param>
    explicit HashSet(const Size capacity) :
      table(NP2(capacity)) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="values">Initial values.</param>
    template<Size N>
    HashSet(const ValueType(&values)[N]) : HashSet(N) {
      for (const auto& value : values) {
        this->add(value);
      }
    }
    /// <summary>
    /// Default constructor.
    /// </summary>
    HashSet() :
      table() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashSet(const HashSet& other) :
      table(other.table) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    HashSet(HashSet&& other) noexcept :
      table(Move(other.table)) {}
  public:
    /// <summary>
    /// Get the hash set capacity.
    /// </summary>
    /// <returns>Returns the hash set capacity.</returns>
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
    /// Get the number of values in the hash set.
    /// </summary>
    /// <returns>Returns the hash set size.</returns>
    Size getSize() const override {
      return this->table.getSize();
    }
    /// <summary>
    /// Determines whether or not the hash set is empty.
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
      auto* iterator = new EntryIterator<H, T>(this->table);
      return UniqueIterator<EntryType>(iterator);
    }
    /// <summary>
    /// Add the specified value in the hash set by using move semantics.
    /// When the load factor is greater than or equals to 0.7f the current capacity will double.
    /// </summary>
    /// <param name="value">Value.</param>
    void add(ValueType&& value) override {
      if (this->getLoadFactor() >= 0.7f) {
        this->table.enlarge(this->getCapacity() << 1);
      }
      this->table.set(Forward<ValueType>(value));
    }
    /// <summary>
    /// Add a copy of the specified value in the hash set.
    /// When the load factor is greater than or equals to 0.7f the current capacity will double.
    /// </summary>
    /// <param name="value">Value.</param>
    void add(const ValueType& value) override {
      ValueType copy(value);
      this->add(Move(copy));
    }
    /// <summary>
    /// Determines whether or not the hash set contains the specified value.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was found, false otherwise.</returns>
    bool has(const ValueType& value) const override {
      return this->table.get(value) != nullptr;
    }
    /// <summary>
    /// Remove the specified value from the hash set.
    /// When the load factor is less than or equals to 0.3f the hash set capacity will reduce by half.
    /// </summary>
    /// <param name="value">Value.</param>
    /// <returns>Returns true when the value was removed, false otherwise.</returns>
    bool remove(const ValueType& value) override {
      auto* entry = this->table.unset(value);
      if (entry != nullptr) {
        if (this->getLoadFactor() <= 0.3f) {
          this->table.shrink(this->getCapacity() >> 1);
        }
        return true;
      }
      return false;
    }
    /// <summary>
    /// Clear the hash set.
    /// The current capacity will remains the same.
    /// </summary>
    void clear() override {
      this->table.clear();
    }
  public:
    /// <summary>
    /// Assign all properties from the given set.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    HashSet& operator = (HashSet other) noexcept {
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
