/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./strings/ansi_string.hpp"
#include "./strings/wide_string.hpp"

namespace SPL {
  /// <summary>
  /// ANSI string class.
  /// </summary>
  using AnsiString = Strings::AnsiString;
  /// <summary>
  /// Wide string class.
  /// </summary>
  using WideString = Strings::WideString;
}
