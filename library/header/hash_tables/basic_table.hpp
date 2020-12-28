/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./hash_entry.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Basic table class.
  /// </summary>
  /// <typeparam name="H">Hash function.</typeparam>
  /// <typeparam name="K">Key type.</typeparam>
  /// <typeparam name="...V">Value type.</typeparam>
  template<auto H, typename K, typename ...V>
  class BasicTable final {
  private:
    /// <summary>
    /// Hash entry type.
    /// </summary>
    using EntryType = HashEntry<K, V...>;
    /// <summary>
    /// Non-constant key type.
    /// </summary>
    using KeyType = Metadata::ConstantType<K>;
    /// <summary>
    /// Total number of entries.
    /// </summary>
    Size capacity;
    /// <summary>
    /// Array of entries.
    /// </summary>
    EntryType* entries;
    /// <summary>
    /// Current number of entries.
    /// </summary>
    Size size;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(BasicTable& source, BasicTable& target) noexcept {
      using SPL::Swap;
      Swap(source.capacity, target.capacity);
      Swap(source.entries, target.entries);
      Swap(source.size, target.size);
    }
    /// <summary>
    /// Load the entry index that corresponds to the specified hash and/or key.
    /// </summary>
    /// <param name="hash">Entry hash.</param>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns the index of the corresponding entry.</returns>
    Index load(const Id hash, const KeyType& key) const {
      Index preferred = -1;
      for (Size offset = 0; offset < this->capacity; ++offset) {
        const Index index = (hash + offset) % this->capacity;
        auto& entry = this->entries[index];
        if (entry.state == EntryState::Occupied) {
          if (Compare(entry.key, key) == 0) {
            return index;
          }
          continue;
        }
        if (preferred == -1) {
          preferred = index;
        }
        if (entry.state == EntryState::Free) {
          break;
        }
      }
      return preferred;
    }
    /// <summary>
    /// Resize the current capacity based on the given capacity and rehash all entries.
    /// IMPORTANT: Make sure the new capacity can store all the current entries.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    void resize(const Size capacity) {
      using SPL::Swap;
      BasicTable table(capacity);
      for (Size offset = 0; table.size < this->size; ++offset) {
        auto& entry = this->entries[offset];
        if (entry.state == EntryState::Occupied) {
          const auto index = table.load(entry.hash, entry.key);
          Swap(table.entries[index], entry);
          table.size++;
        }
      }
      this->size = 0;
      Swap(*this, table);
    }
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="capacity">Initial capacity.</param>
    explicit BasicTable(const Size capacity) :
      capacity(Math::Max(capacity, 4U)), entries(new EntryType[this->capacity]()), size(0) {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    BasicTable() :
      capacity(0), entries(nullptr), size(0) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicTable(const BasicTable& other) : BasicTable(other.capacity) {
      for (Size offset = 0; this->size < other.size; ++offset) {
        auto& entry = other.entries[offset];
        if (entry.state == EntryState::Occupied) {
          const auto index = this->load(entry.hash, entry.key);
          this->entries[index] = entry;
          this->size++;
        }
      }
    }
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicTable(BasicTable&& other) noexcept : BasicTable() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~BasicTable() {
      delete[] this->entries;
    }
  public:
    /// <summary>
    /// Get the capacity of the table.
    /// </summary>
    /// <returns>Returns the table capacity.</returns>
    Size getCapacity() const {
      return this->capacity;
    }
    /// <summary>
    /// Get the number of entries in the table.
    /// </summary>
    /// <returns>Returns the table size.</returns>
    Size getSize() const {
      return this->size;
    }
    /// <summary>
    /// Set an entry for the specified key by using move semantics.
    /// If the entry doesn't exists try to create a new one.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns a pointer to the corresponding entry or null when isn't possible to set it.</returns>
    EntryType* set(KeyType&& key) {
      const auto hash = H(key);
      const auto index = this->load(hash, key);
      if (index != -1) {
        auto& entry = this->entries[index];
        if (entry.state != EntryState::Occupied) {
          using SPL::Swap;
          Swap(entry.key, key);
          entry.hash = hash;
          entry.state = EntryState::Occupied;
          this->size++;
        }
        return &entry;
      }
      return nullptr;
    }
    /// <summary>
    /// Set an entry for a copy of the specified key.
    /// If the entry doesn't exists try to create a new one.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns a pointer to the corresponding entry or null when isn't possible to set it.</returns>
    EntryType* set(const K& key) {
      KeyType copy(key);
      return this->set(Move(copy));
    }
    /// <summary>
    /// Get an entry that corresponds to the specified key.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns a pointer to the corresponding entry or null when isn't possible to get it.</returns>
    EntryType* get(const K& key) const {
      const auto index = this->load(H(key), key);
      if (index != -1) {
        auto& entry = this->entries[index];
        if (entry.state == EntryState::Occupied) {
          return &entry;
        }
      }
      return nullptr;
    }
    /// <summary>
    /// Unset an entry that corresponds to the specified key.
    /// The current capacity will remains the same.
    /// </summary>
    /// <param name="key">Entry key.</param>
    /// <returns>Returns a pointer to the corresponding entry or null when isn't possible to unset it.</returns>
    EntryType* unset(const K& key) {
      auto* entry = this->get(key);
      if (entry != nullptr) {
        entry->state = EntryState::Deleted;
        this->size--;
        return entry;
      }
      return nullptr;
    }
    /// <summary>
    /// Clear the table.
    /// The current capacity will remains the same.
    /// </summary>
    void clear() {
      for (Size offset = 0; offset < this->capacity; ++offset) {
        auto& entry = this->entries[offset];
        entry.state = EntryState::Free;
      }
      this->size = 0;
    }
    /// <summary>
    /// Enlarge the current capacity and rehash all entries.
    /// The new capacity should be greater than the current one.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    void enlarge(const Size capacity) {
      const auto newer = Math::Max(capacity, 4U);
      if (newer > this->capacity) {
        this->resize(newer);
      }
    }
    /// <summary>
    /// Shrink the current capacity and rehash all entries.
    /// The new capacity should be smaller than the current one and greater than the current size.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    void shrink(const Size capacity) {
      const auto newer = Math::Max(capacity, 4U);
      if (newer > this->size && newer < this->capacity) {
        this->resize(newer);
      }
    }
  public:
    /// <summary>
    /// Assign all properties from the given table.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    BasicTable& operator = (BasicTable other) noexcept {
      Swap(*this, other);
      return *this;
    }
    /// <summary>
    /// Get the array of entries.
    /// </summary>
    /// <returns>Returns the array of entries.</returns>
    operator const EntryType* () const {
      return this->entries;
    }
  };
}
