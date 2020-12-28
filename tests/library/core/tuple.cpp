/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "core.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Core::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(TupleTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Tuple<int> tuple;
      // Check state.
      Assert::AreEqual(1U, tuple.getLength());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Tuple tuple(10, 1.0f, true);
      // Check state.
      Assert::AreEqual(3U, tuple.getLength());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      Tuple tuple(10, 1.0f, true), other(tuple);
      // Check copy.
      Assert::AreEqual(tuple.get<0>(), other.get<0>());
      Assert::AreEqual(tuple.get<1>(), other.get<1>());
      Assert::AreEqual(tuple.get<2>(), other.get<2>());
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      Tuple tuple(10, 1.0f, true), other(Move(tuple));
      // Check tuple values.
      Assert::AreEqual(0, tuple.get<0>());
      Assert::AreEqual(0.0f, tuple.get<1>());
      Assert::AreEqual(false, tuple.get<2>());
      // Check other values.
      Assert::AreEqual(10, other.get<0>());
      Assert::AreEqual(1.0f, other.get<1>());
      Assert::AreEqual(true, other.get<2>());
    }
    /// <summary>
    /// Test the get method.
    /// </summary>
    TEST_METHOD(MethodGet) {
      Tuple tuple(10, 1.0f, true);
      // Check values.
      Assert::AreEqual(10, tuple.get<0>());
      Assert::AreEqual(1.0f, tuple.get<1>());
      Assert::AreEqual(true, tuple.get<2>());
    }
    /// <summary>
    /// Test the set method.
    /// </summary>
    TEST_METHOD(MethodSet) {
      Tuple tuple(10, 1.0f, true);
      // Set values.
      Assert::AreEqual(10, tuple.set<0>(20));
      Assert::AreEqual(1.0f, tuple.set<1>(2.0f));
      Assert::AreEqual(true, tuple.set<2>(false));
      // Check values.
      Assert::AreEqual(20, tuple.get<0>());
      Assert::AreEqual(2.0f, tuple.get<1>());
      Assert::AreEqual(false, tuple.get<2>());
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      Tuple<int, float, bool> tuple(10, 1.0f, true), other;
      // Copy to other.
      other = tuple;
      // Check copy.
      Assert::AreEqual(tuple.get<0>(), other.get<0>());
      Assert::AreEqual(tuple.get<1>(), other.get<1>());
      Assert::AreEqual(tuple.get<2>(), other.get<2>());
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      Tuple<int, float, bool> tuple(10, 1.0f, true), other;
      // Move to other.
      other = Move(tuple);
      // Check tuple values.
      Assert::AreEqual(0, tuple.get<0>());
      Assert::AreEqual(0.0f, tuple.get<1>());
      Assert::AreEqual(false, tuple.get<2>());
      // Check other values.
      Assert::AreEqual(10, other.get<0>());
      Assert::AreEqual(1.0f, other.get<1>());
      Assert::AreEqual(true, other.get<2>());
    }
  };
}
