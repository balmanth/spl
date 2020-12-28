/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"

namespace SPL::Hashes {
  /// <summary>
  /// Generic FNV-1 hash function.
  /// This function uses the FNV-1 hash. For more info, please visit:
  /// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
  /// </summary>
  /// <typeparam name="T">Input type.</typeparam>
  template<typename T>
  class FNV1 final : public SPL::Hash<T> {
  private:
    /// <summary>
    /// Hash value.
    /// </summary>
    Id hash;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    FNV1() :
      hash(0x811C9DC5) {}
    /// <summary>
    /// Get the current hash.
    /// </summary>
    /// <returns>Returns the current hash.</returns>
    Id getHash() const {
      return this->hash;
    }
    /// <summary>
    /// Generate the next hash based on the given value.
    /// </summary>
    /// <param name="value">Value for the next hash.</param>
    void next(const T& value) {
      this->hash *= 0x01000193;
      this->hash ^= value;
    }
  };
}
