/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../interfaces/exception.hpp"
#include "../core/types.hpp"

namespace SPL::Exceptions {
  /// <summary>
  /// Index out of bounds, exception class.
  /// </summary>
  class IndexOutOfBounds : public Exception {
  private:
    /// <summary>
    /// Index value.
    /// </summary>
    const Index index;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="index">Exception index.</param>
    IndexOutOfBounds(const Index index) :
      index(index) {}
    /// <summary>
    /// Get the exception index.
    /// </summary>
    /// <returns>Returns the exception index.</returns>
    const Index getIndex() const {
      return this->index;
    }
  };
}
