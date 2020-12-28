/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::HashTables {
  /// <summary>
  /// Default hash function for raw keys.
  /// </summary>
  /// <typeparam name="T">Key type.</typeparam>
  /// <param name="key">Entry key.</param>
  /// <returns>Returns the hash code.</returns>
  template<typename T>
  inline Id Function(const T& key) {
    using KeyType = Types::SelectType<Metadata::IsPointer<T>, Metadata::PointerType<T>, T>;
    static_assert(Metadata::IsIntegerConvertible<KeyType>, "SPL::HashTables::Function isn't implemented for the given key type (T).");
    if constexpr (!Metadata::IsPointer<T>) {
      return static_cast<Id>(key);
    }
    else {
      Hashes::FNV1<KeyType> fnv1;
      if (key != nullptr) {
        const auto* entries = key;
        while (*entries != KeyType()) {
          fnv1.next(*entries++);
        }
      }
      return fnv1.getHash();
    }
  }
  /// <summary>
  /// Default hash function for string keys.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <param name="key">Entry key.</param>
  /// <returns>Returns the hash code.</returns>
  template<typename T>
  inline Id Function(const SPL::String<T>& key) {
    Hashes::FNV1<T> fnv1;
    const auto length = key.getLength();
    for (auto index = 0; index < length; ++index) {
      fnv1.next(key[index]);
    }
    return fnv1.getHash();
  }
}
