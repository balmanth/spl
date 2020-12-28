/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "pointers.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SPL::Tests;

namespace SPL::Pointers::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(UniquePointerTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Unique<int> pointer;
      // Check state.
      Assert::IsFalse(pointer);
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Unique<int> pointer(new int);
      // Check state.
      Assert::IsTrue(pointer);
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      Unique<int> pointer(new int);
      /// Check pointer state.
      Assert::IsTrue(pointer);
      // Move pointer to other.
      Unique<int> other(Move(pointer));
      /// Check other state.
      Assert::IsTrue(other);
      // Check pointer state.
      Assert::IsFalse(pointer);
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      // Instances counter.
      Size instances = 0;
      // Create a new instance.
      Unique<Mock>* pointer = new Unique<Mock>(new Mock(instances));
      Assert::AreEqual(1U, instances);
      // Delete the instance.
      delete pointer;
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the release method.
    /// </summary>
    TEST_METHOD(MethodRelease) {
      Unique<int> pointer(new int);
      // Check state.
      Assert::IsTrue(pointer);
      // Release memory.
      pointer.release();
      // Check state.
      Assert::IsFalse(pointer);
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      Unique<int> pointer(new int);
      // Check pointer state.
      Assert::IsTrue(pointer);
      Unique<int> other;
      // Move pointer to other.
      other = Move(pointer);
      /// Check other state.
      Assert::IsTrue(other);
      // Check pointer state.
      Assert::IsFalse(pointer);
    }
    /// <summary>
    /// Test the dereference operator.
    /// </summary>
    TEST_METHOD(OperatorDereference) {
      Unique<int> pointer(new int(10));
      // Check values.
      Assert::AreEqual(10, *pointer);
    }
    /// <summary>
    /// Test the subscript operator.
    /// </summary>
    TEST_METHOD(OperatorAccess) {
      Unique<int> pointer(new int[3]{ 10, 10, 10 });
      // Check values.
      Assert::AreEqual(10, pointer[0]);
      Assert::AreEqual(10, pointer[1]);
      Assert::AreEqual(10, pointer[2]);
    }
  };
}
