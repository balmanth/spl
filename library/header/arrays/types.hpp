/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core.hpp"
#include "../math.hpp"
#include "../pointers.hpp"
#include "../interfaces.hpp"
#include "../exceptions.hpp"
#include "../metadata.hpp"
#include "../pointers.hpp"

namespace SPL::Arrays {
  /// <summary>
  /// Basic array class declaration.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  class BasicArray;
  /// <summary>
  /// Array iterator class declaration.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  class ArrayIterator;
  /// <summary>
  /// List pack class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  using ListPack = Pack<List<T>>;
  /// <summary>
  /// Unique list class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  using UniqueList = Unique<List<T>>;
  /// <summary>
  /// Unique iterator class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  using UniqueIterator = Unique<Iterator<T>>;
}
