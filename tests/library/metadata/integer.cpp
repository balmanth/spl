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
  TEST_CLASS(IntegerTests)
  {
  public:
    /// <summary>
    /// Test the 'IsConvertible' property.
    /// </summary>
    TEST_METHOD(PropertyConvertible) {
      // Normal type.
      Assert::IsTrue(IsIntegerConvertible<bool>);
      Assert::IsTrue(IsIntegerConvertible<wchar_t>);
      Assert::IsTrue(IsIntegerConvertible<char16_t>);
      Assert::IsTrue(IsIntegerConvertible<char32_t>);
      Assert::IsTrue(IsIntegerConvertible<char>);
      Assert::IsTrue(IsIntegerConvertible<signed char>);
      Assert::IsTrue(IsIntegerConvertible<signed short>);
      Assert::IsTrue(IsIntegerConvertible<signed int>);
      Assert::IsTrue(IsIntegerConvertible<signed long>);
      Assert::IsTrue(IsIntegerConvertible<signed long long>);
      Assert::IsTrue(IsIntegerConvertible<unsigned char>);
      Assert::IsTrue(IsIntegerConvertible<unsigned short>);
      Assert::IsTrue(IsIntegerConvertible<unsigned int>);
      Assert::IsTrue(IsIntegerConvertible<unsigned long>);
      Assert::IsTrue(IsIntegerConvertible<unsigned long long>);
      // Constant type.
      Assert::IsTrue(IsIntegerConvertible<const bool>);
      Assert::IsTrue(IsIntegerConvertible<const wchar_t>);
      Assert::IsTrue(IsIntegerConvertible<const char16_t>);
      Assert::IsTrue(IsIntegerConvertible<const char32_t>);
      Assert::IsTrue(IsIntegerConvertible<const char>);
      Assert::IsTrue(IsIntegerConvertible<const signed char>);
      Assert::IsTrue(IsIntegerConvertible<const signed short>);
      Assert::IsTrue(IsIntegerConvertible<const signed int>);
      Assert::IsTrue(IsIntegerConvertible<const signed long>);
      Assert::IsTrue(IsIntegerConvertible<const signed long long>);
      Assert::IsTrue(IsIntegerConvertible<const unsigned char>);
      Assert::IsTrue(IsIntegerConvertible<const unsigned short>);
      Assert::IsTrue(IsIntegerConvertible<const unsigned int>);
      Assert::IsTrue(IsIntegerConvertible<const unsigned long>);
      Assert::IsTrue(IsIntegerConvertible<const unsigned long long>);
    }
  };
}
