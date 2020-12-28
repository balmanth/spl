/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "metadata.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Metadata::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(CharacterTests)
  {
  public:
    /// <summary>
    /// Test the 'IsConvertible' property.
    /// </summary>
    TEST_METHOD(PropertyConvertible) {
      // Normal type.
      Assert::IsTrue(IsCharacterConvertible<wchar_t>);
      Assert::IsTrue(IsCharacterConvertible<char16_t>);
      Assert::IsTrue(IsCharacterConvertible<char32_t>);
      Assert::IsTrue(IsCharacterConvertible<char>);
      Assert::IsTrue(IsCharacterConvertible<signed char>);
      Assert::IsTrue(IsCharacterConvertible<unsigned char>);
      // Constant type.
      Assert::IsTrue(IsCharacterConvertible<const wchar_t>);
      Assert::IsTrue(IsCharacterConvertible<const char16_t>);
      Assert::IsTrue(IsCharacterConvertible<const char32_t>);
      Assert::IsTrue(IsCharacterConvertible<const char>);
      Assert::IsTrue(IsCharacterConvertible<const signed char>);
      Assert::IsTrue(IsCharacterConvertible<const unsigned char>);
    }
  };
}
