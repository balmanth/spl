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

namespace SPL::Strings {
  /// <summary>
  /// Basic string class declaration.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class BasicString;
  /// <summary>
  /// String iterator class declaration.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class StringIterator;
  /// <summary>
  /// String pack class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using StringPack = Pack<String<T>>;
  /// <summary>
  /// Unique string class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using UniqueString = Unique<String<T>>;
  /// <summary>
  /// Unique iterator class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using UniqueIterator = Unique<Iterator<T>>;
}
