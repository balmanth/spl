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
  TEST_CLASS(PackTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Pack<int> pack;
      // Check state.
      Assert::AreEqual(0U, pack.getLength());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Pack<int> pack(0, 1, 2);
      // Check state.
      Assert::AreEqual(3U, pack.getLength());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      Pack<int> pack(0, 1, 2);
      Pack<int> other(pack);
      // Check copy state.
      Assert::AreEqual(pack.isEmpty(), other.isEmpty());
      Assert::AreEqual(pack.getLength(), other.getLength());
      // Check copy values.
      for (Index index = 0; index < pack.getLength(); ++index) {
        Assert::AreEqual(pack.get(index), other.get(index));
      }
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      Pack<int>* pack = new Pack<int>(0, 1, 2);
      Pack<int> other(Move(*pack));
      // Check pack state.
      Assert::IsTrue(pack->isEmpty());
      Assert::AreEqual(0U, pack->getLength());
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getLength());
      // Check other values.
      for (Index index = 0; index < pack->getLength(); ++index) {
        Assert::AreEqual<int>(index, other.get(index));
      }
      delete pack;
    }
    /// <summary>
    /// Test the get method.
    /// </summary>
    TEST_METHOD(MethodGet) {
      Pack<int> pack(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
      // Check values.
      for (Index index = 0; index < pack.getLength(); ++index) {
        Assert::AreEqual<int>(index, pack.get(index));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      Pack<int> pack(0, 1, 2);
      Pack<int> other;
      // Copy
      other = pack;
      // Check copy state.
      Assert::AreEqual(pack.isEmpty(), other.isEmpty());
      Assert::AreEqual(pack.getLength(), other.getLength());
      // Check copy values.
      for (Index index = 0; index < pack.getLength(); ++index) {
        Assert::AreEqual(pack.get(index), other.get(index));
      }
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      Pack<int>* pack = new Pack<int>(0, 1, 2);
      Pack<int> other;
      // Move to other.
      other = Move(*pack);
      // Check pack state.
      Assert::IsTrue(pack->isEmpty());
      Assert::AreEqual(0U, pack->getLength());
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getLength());
      // Check other values.
      for (Index index = 0; index < other.getLength(); ++index) {
        Assert::AreEqual<int>(index, other.get(index));
      }
      delete pack;
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccess) {
      Pack<int> pack(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
      // Check values.
      for (Index index = 0; index < pack.getLength(); ++index) {
        Assert::AreEqual<int>(index, pack[index]);
      }
    }
  };
}
