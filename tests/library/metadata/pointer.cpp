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
  TEST_CLASS(PointerTests)
  {
  public:
    /// <summary>
    /// Test the 'Is' property.
    /// </summary>
    TEST_METHOD(PropertyIs) {
      // Pointer type.
      Assert::IsTrue(IsPointer<int*>);
      Assert::IsTrue(IsPointer<int**>);
      Assert::IsTrue(IsPointer<int***>);
      // Non-pointer type.
      Assert::IsFalse(IsPointer<int>);
    }
  };
}
