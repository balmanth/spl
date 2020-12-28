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
  TEST_CLASS(SharedPointerTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Shared<int> pointer;
      // Check state.
      Assert::IsFalse(pointer);
      Assert::AreEqual(0U, pointer.getReferences());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Shared<int> pointer(new int);
      // Check state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      Shared<int> pointer(new int);
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      // Copy pointer to other.
      Shared<int> other(pointer);
      // Check other state.
      Assert::IsTrue(other);
      Assert::AreEqual(2U, other.getReferences());
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(2U, pointer.getReferences());
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      // Instances counter.
      Size instances = 0;
      // Create a new instance.
      Shared<Mock>* pointer = new Shared<Mock>(new Mock(instances));
      Assert::AreEqual(1U, instances);
      // Delete the instance.
      delete pointer;
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the release method.
    /// </summary>
    TEST_METHOD(MethodRelease) {
      Shared<int> pointer(new int);
      // Check state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      // Release memory.
      pointer.release();
      // Check state.
      Assert::IsFalse(pointer);
      Assert::AreEqual(0U, pointer.getReferences());
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      Shared<int> pointer(new int);
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      Shared<int> other;
      // Copy pointer to other.
      other = pointer;
      /// Check other state.
      Assert::IsTrue(other);
      Assert::AreEqual(2U, other.getReferences());
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(2U, pointer.getReferences());
    }
    /// <summary>
    /// Test the dereference operator.
    /// </summary>
    TEST_METHOD(OperatorDereference) {
      Shared<int> pointer(new int(10));
      // Check values.
      Assert::AreEqual(10, *pointer);
    }
    /// <summary>
    /// Test the subscript operator.
    /// </summary>
    TEST_METHOD(OperatorAccess) {
      Shared<int> pointer(new int[3]{ 10, 10, 10 });
      // Check values.
      Assert::AreEqual(10, pointer[0]);
      Assert::AreEqual(10, pointer[1]);
      Assert::AreEqual(10, pointer[2]);
    }
  };
}
