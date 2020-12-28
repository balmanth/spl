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
  TEST_CLASS(SelectTests)
  {
  public:
    /// <summary>
    /// Test the state property.
    /// </summary>
    TEST_METHOD(PropertyState) {
      Assert::IsTrue(Select<true, void, void>::State);
      Assert::IsFalse(Select<false, void, void>::State);
    }
    /// <summary>
    /// Test the type property.
    /// </summary>
    TEST_METHOD(PropertyType) {
      Assert::IsTrue(Metadata::IsInteger<SelectType<true, int, void>>);
      Assert::IsTrue(Metadata::IsInteger<SelectType<false, void, int>>);
    }
  };
}
