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
  TEST_CLASS(PickTests)
  {
  public:
    /// <summary>
    /// Test the type property.
    /// </summary>
    TEST_METHOD(PropertyType) {
      Assert::IsTrue(Metadata::IsInteger<PickType<0, int, float, bool, int>>);
      Assert::IsTrue(Metadata::IsInteger<PickType<3, int, float, bool, int>>);
    }
  };
}
