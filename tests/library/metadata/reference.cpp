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
  TEST_CLASS(ReferenceTests)
  {
  public:
    /// <summary>
    /// Test the 'Is' property.
    /// </summary>
    TEST_METHOD(PropertyIs) {
      // Reference type.
      Assert::IsTrue(IsReference<int&>);
      Assert::IsTrue(IsReference<int&&>);
      // Non-reference type.
      Assert::IsFalse(IsReference<int>);
    }
    /// <summary>
    /// Test the 'IsLValue' property.
    /// </summary>
    TEST_METHOD(PropertyIsLValue) {
      // LValue reference type.
      Assert::IsTrue(IsLValueReference<int&>);
      // Non-lvalue reference type.
      Assert::IsFalse(IsLValueReference<int&&>);
      Assert::IsFalse(IsLValueReference<int>);
    }
    /// <summary>
    /// Test the 'IsRValue' property.
    /// </summary>
    TEST_METHOD(PropertyIsRValue) {
      // Rvalue reference type.
      Assert::IsTrue(IsRValueReference<int&&>);
      // Non-rvalue reference type.
      Assert::IsFalse(IsRValueReference<int&>);
      Assert::IsFalse(IsRValueReference<int>);
    }
  };
}
