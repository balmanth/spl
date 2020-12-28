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
  TEST_CLASS(DecimalTests)
  {
  public:
    /// <summary>
    /// Test the 'IsConvertible' property.
    /// </summary>
    TEST_METHOD(PropertyConvertible) {
      // Normal type.
      Assert::IsTrue(IsDecimalConvertible<float>);
      Assert::IsTrue(IsDecimalConvertible<double>);
      Assert::IsTrue(IsDecimalConvertible<long double>);
      // Constant type.
      Assert::IsTrue(IsDecimalConvertible<const float>);
      Assert::IsTrue(IsDecimalConvertible<const double>);
      Assert::IsTrue(IsDecimalConvertible<const long double>);
    }
  };
}
