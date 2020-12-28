/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Entry iterator class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  template<auto H, typename K, typename ...V>
  class EntryIterator : public Iterator<HashEntry<K, V...>> {
  private:
    /// <summary>
    /// Basic table type.
    /// </summary>
    using BasicType = BasicTable<H, K, V...>;
    /// <summary>
    /// Hash entry type.
    /// </summary>
    using EntryType = HashEntry<K, V...>;
    /// <summary>
    /// Basic table reference.
    /// </summary>
    const BasicType& table;
    /// <summary>
    /// Current count.
    /// </summary>
    Size count;
    /// <summary>
    /// Current index.
    /// </summary>
    Index index;
  private:
    /// <summary>
    /// Find to the next entry.
    /// </summary>
    /// <returns>Returns the next entry or null when there's no next entry.</returns>
    const EntryType* findNext() {
      while (this->index < this->table.getCapacity()) {
        const auto* entry = &this->table[this->index++];
        if (entry->getState() == EntryState::Occupied) {
          this->count++;
          return entry;
        }
      }
      return nullptr;
    }
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="table">Initial table.</param>
    EntryIterator(const BasicType& table) :
      table(table), count(0), index(0) {}
  public:
    /// <summary>
    /// Check whether or not the iterator has the next entry.
    /// </summary>
    /// <returns>Returns true when the next entry exists, false otherwise.</returns>
    bool hasNext() const override {
      return this->count < this->table.getSize();
    }
    /// <summary>
    /// Move to the next entry and get the current one.
    /// </summary>
    /// <returns>Returns the current entry.</returns>
    /// <exception cref="SPL::Exceptions::InvalidOperation">Throws when there's no next entry.</exception>
    const EntryType& next() override {
      const auto* entry = this->findNext();
      if (entry == nullptr) {
        throw Exceptions::InvalidOperation();
      }
      return *entry;
    }
  };
}
