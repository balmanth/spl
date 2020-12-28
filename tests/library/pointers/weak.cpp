/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "pointers.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Pointers::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(WeakPointerTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Weak<int> pointer;
      // Check state.
      Assert::IsFalse(pointer);
      Assert::AreEqual(0U, pointer.getReferences());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Shared<int> source(new int);
      Weak<int> pointer(source);
      // Check state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      Shared<int> source(new int);
      Weak<int> pointer(source);
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      // Copy pointer to other.
      Weak<int> other(pointer);
      // Check other state.
      Assert::IsTrue(other);
      Assert::AreEqual(1U, other.getReferences());
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
    }
    /// <summary>
    /// Test the get method.
    /// </summary>
    TEST_METHOD(MethodGet) {
      Shared<int> source(new int);
      Weak<int> pointer(source);
      // Check state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      // Get a weak pointer copy.
      if (Shared<int> copy = pointer.get()) {
        // Check new state.
        Assert::IsTrue(pointer);
        Assert::AreEqual(2U, pointer.getReferences());
      }
      // Check new state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
    }
    /// <summary>
    /// Test the release method.
    /// </summary>
    TEST_METHOD(MethodRelease) {
      Shared<int> source(new int);
      Weak<int> pointer(source);
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
      Shared<int> source(new int);
      Weak<int> pointer(source);
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
      Weak<int> other;
      // Copy pointer to other.
      other = pointer;
      /// Check other state.
      Assert::IsTrue(other);
      Assert::AreEqual(1U, other.getReferences());
      // Check pointer state.
      Assert::IsTrue(pointer);
      Assert::AreEqual(1U, pointer.getReferences());
    }
    /// <summary>
    /// Test the release feature.
    /// </summary>
    TEST_METHOD(FeatureRelease) {
      Shared<int> source(new int);
      Weak<int> pointer1(source), pointer2(source);
      // Check states.
      Assert::IsTrue(pointer1);
      Assert::AreEqual(1U, pointer1.getReferences());
      Assert::IsTrue(pointer2);
      Assert::AreEqual(1U, pointer2.getReferences());
      // Release memory.
      source.release();
      // Check states.
      Assert::IsFalse(pointer1);
      Assert::AreEqual(0U, pointer1.getReferences());
      Assert::IsFalse(pointer2);
      Assert::AreEqual(0U, pointer2.getReferences());
    }
  };
}
