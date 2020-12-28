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
  TEST_CLASS(PairTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Pair<int, float> pair;
      // Check state.
      Assert::AreEqual(0, pair.key);
      Assert::AreEqual(0.0f, pair.value);
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Pair<int, float> pair(10, 1.0f);
      // Check state.
      Assert::AreEqual(10, pair.key);
      Assert::AreEqual(1.0f, pair.value);
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      Pair<int, float> pair(10, 1.0f), other(pair);
      // Check copy.
      Assert::AreEqual(pair.key, other.key);
      Assert::AreEqual(other.value, pair.value);
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      Pair<int, float> pair(10, 1.0f), other(Move(pair));
      // Check pair state.
      Assert::AreEqual(0, pair.key);
      Assert::AreEqual(0.0f, pair.value);
      // Check other state.
      Assert::AreEqual(10, other.key);
      Assert::AreEqual(1.0f, other.value);
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      Pair<int, float> pair(10, 1.0f), other;
      // Copy to other.
      other = pair;
      // Check copy.
      Assert::AreEqual(pair.key, other.key);
      Assert::AreEqual(other.value, pair.value);
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      Pair<int, float> pair(10, 1.0f), other;
      // Move to other.
      other = Move(pair);
      // Check pair state.
      Assert::AreEqual(0, pair.key);
      Assert::AreEqual(0.0f, pair.value);
      // Check other state.
      Assert::AreEqual(10, other.key);
      Assert::AreEqual(1.0f, other.value);
    }
  };
}
