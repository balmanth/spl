/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "metadata.hpp"
#include "types.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Types::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(SameTests)
  {
  public:
    /// <summary>
    /// Test the state property.
    /// </summary>
    TEST_METHOD(PropertyState) {
      // Are the same.
      Assert::IsTrue(AreSame<int, int>);
      Assert::IsTrue(AreSame<int, int, int>);
      // Aren't the same.
      Assert::IsFalse(AreSame<int, long>);
      Assert::IsFalse(AreSame<int, int, int, long>);
    }
  };
}
