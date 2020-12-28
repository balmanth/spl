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
  TEST_CLASS(ClassTests)
  {
  private:
    /// <summary>
    /// Test class.
    /// </summary>
    class TestClass {};
  public:
    /// <summary>
    /// Test the 'Is' property.
    /// </summary>
    TEST_METHOD(PropertyIs) {
      // Class type.
      Assert::IsTrue(IsClass<TestClass>);
      Assert::IsTrue(IsClass<const TestClass>);
      // Not a class type.
      Assert::IsFalse(IsClass<TestClass*>);
      Assert::IsFalse(IsClass<TestClass&>);
    }
  };
}
