/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./arrays/array_list.hpp"

namespace SPL {
  /// <summary>
  /// Array list class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  using ArrayList = Arrays::ArrayList<T>;
}
