/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../interfaces/exception.hpp"

namespace SPL::Exceptions {
  /// <summary>
  /// Invalid argument, exception class.
  /// </summary>
  class InvalidArgument : public Exception {
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    InvalidArgument() = default;
  };
}
