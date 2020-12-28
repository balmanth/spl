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
  TEST_CLASS(ConstantTests)
  {
  public:
    /// <summary>
    /// Test the 'Is' property.
    /// </summary>
    TEST_METHOD(PropertyIs) {
      // Normal type.
      Assert::IsFalse(IsConstant<int>);
      Assert::IsFalse(IsConstant<double>);
      // Constant type.
      Assert::IsTrue(IsConstant<const int>);
      Assert::IsTrue(IsConstant<const double>);
    }
  };
}
