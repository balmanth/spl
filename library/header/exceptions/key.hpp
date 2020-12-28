/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../interfaces/exception.hpp"

namespace SPL::Exceptions {
  /// <summary>
  /// Key not found, exception class.
  /// </summary>
  /// <typeparam name="K">Key type.</typeparam>
  template<typename K>
  class KeyNotFound : public Exception {
  private:
    /// <summary>
    /// Key value.
    /// </summary>
    const K key;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="key">Exception key.</param>
    KeyNotFound(const K& key) :
      key(key) {}
    /// <summary>
    /// Get the exception key.
    /// </summary>
    /// <returns>Returns the exception key.</returns>
    const K& getKey() const {
      return this->key;
    }
  };
}
