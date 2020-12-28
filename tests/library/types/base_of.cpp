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
  TEST_CLASS(BaseOfTests)
  {
  private:
    /// <summary>
    /// Test class.
    /// </summary>
    class TestClass {};
    /// <summary>
    /// Base test class.
    /// </summary>
    class TestBase {};
    /// <summary>
    /// Derived test class.
    /// </summary>
    class TestDerived : public TestBase {};
  public:
    /// <summary>
    /// Test the state property.
    /// </summary>
    TEST_METHOD(PropertyState) {
      // Is base of.
      Assert::IsTrue(IsBaseOf<TestBase, TestDerived>);
      Assert::IsTrue(IsBaseOf<TestBase, TestDerived, TestDerived>);
      // Isn't base of.
      Assert::IsFalse(IsBaseOf<TestBase, TestBase>);
      Assert::IsFalse(IsBaseOf<TestBase, TestClass>);
      Assert::IsFalse(IsBaseOf<TestBase, TestDerived, TestBase>);
      Assert::IsFalse(IsBaseOf<TestDerived, TestClass>);
      Assert::IsFalse(IsBaseOf<TestDerived, TestBase>);
      Assert::IsFalse(IsBaseOf<int, int>);
    }
  };
}
