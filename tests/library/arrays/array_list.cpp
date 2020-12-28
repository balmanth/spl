/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "arrays.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SPL::Tests;

namespace SPL::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(ArrayListTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      ArrayList<const float> list;
      // Check state.
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(0U, list.getCapacity());
    }
    /// <summary>
    /// Test the capacity constructor.
    /// </summary>
    TEST_METHOD(ConstructCapacity) {
      ArrayList<const float> list(2);
      // Check state.
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity()); // <~ The minimum capacity is 4.
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f });
      // Check state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(3U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values), other(list);
      // Check copy state.
      Assert::AreEqual(list.isEmpty(), other.isEmpty());
      Assert::AreEqual(list.getLength(), other.getLength());
      Assert::AreEqual(list.getCapacity(), other.getCapacity());
      // Check copy values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(list.get(index), other.get(index));
      }
      // Change values.
      list.set(0, 1.0f);
      list.set(2, 3.0f);
      // Check other values.
      Assert::AreNotEqual(list.get(0), other.get(0));
      Assert::AreEqual(list.get(1), other.get(1));
      Assert::AreNotEqual(list.get(2), other.get(2));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values), other(Move(list));
      // Check list state.
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(0U, list.getCapacity());
      // Check list values.
      for (const float value : values) {
        Assert::IsFalse(list.contains(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getLength());
      Assert::AreEqual(4U, other.getCapacity());
      // Check other values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(values[index], other.get(index));
      }
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      Size instances = 0;
      // Create a new instance.
      List<Mock>* list = new ArrayList<Mock>({ Mock(instances), Mock(instances), Mock(instances) });
      Assert::AreEqual(3U, instances);
      // Delete the instance.
      delete list;
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the add method.
    /// </summary>
    TEST_METHOD(MethodAdd) {
      ArrayList<const float> list({ 1.5f, 2.5f });
      // Add undefined index.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&list] {
        list.add(-1, 4.5f);
      });
      // Add new value by copy.
      const float value = 3.5;
      list.add(2, value);
      // Add new value by move.
      list.add(1, 2.0);
      // Check new state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(4U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      // Check result values.
      const float result[] = { 1.5f, 2.0f, 2.5f, 3.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list.get(index));
      }
    }
    /// <summary>
    /// Test the concat method.
    /// </summary>
    TEST_METHOD(MethodConcat) {
      ArrayList<const float> inputA({ 1.5f, 2.5f, 3.5f });
      ArrayList<const float> inputB({ 4.5f, 5.5f, 6.5f });
      // Merge values.
      auto list = inputA.concat({ inputB, ArrayList<const float>({ 7.5f, 8.5f, 9.5f }) });
      // Check values.
      const float result[] = { 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list->get(index));
      }
    }
    /// <summary>
    /// Test the set method.
    /// </summary>
    TEST_METHOD(MethodSet) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Set undefined index.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&list] {
        list.set(-1, 4.5f);
      });
      // Set new values by copy.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)) - 1; ++index) {
        Assert::AreEqual(values[index], list.set(index, values[index] + 0.5f));
      }
      // Set new value by move.
      const float value = 4.0;
      Assert::AreEqual(values[2], list.set(2, value));
      // Check new state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(3U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(values[index] + 0.5f, list.get(index));
      }
    }
    /// <summary>
    /// Test the get method (by return).
    /// </summary>
    TEST_METHOD(MethodGetByReturn) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&list] {
        Assert::AreEqual(0.0f, list.get(-1));
      });
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(values[index], list.get(index));
      }
    }
    /// <summary>
    /// Test the get method (by reference).
    /// </summary>
    TEST_METHOD(MethodGetByReference) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      float value;
      // Check undefined value.
      Assert::IsFalse(list.get(-1, value));
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::IsTrue(list.get(index, value));
        Assert::AreEqual(values[index], value);
      }
    }
    /// <summary>
    /// Test the get method (by iterator).
    /// </summary>
    TEST_METHOD(MethodGetByIterator) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Check values.
      auto iterator = list.getIterator();
      for (Index index = 0; iterator->hasNext(); ++index) {
        Assert::AreEqual(values[index], iterator->next());
      }
    }
    /// <summary>
    /// Test the indexOf method.
    /// </summary>
    TEST_METHOD(MethodIndexOf) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f, 1.5f, 2.5f, 3.5f });
      // Check undefined value.
      Assert::AreEqual<Size>(-1, list.indexOf(2.5f, list.getLength() - 1));
      Assert::AreEqual<Size>(-1, list.indexOf(0.0f));
      // Check values.
      Assert::AreEqual(0U, list.indexOf(1.5f));
      Assert::AreEqual(1U, list.indexOf(2.5f));
      Assert::AreEqual(2U, list.indexOf(3.5f));
      Assert::AreEqual(3U, list.indexOf(1.5f, 1));
      Assert::AreEqual(4U, list.indexOf(2.5f, 2));
      Assert::AreEqual(5U, list.indexOf(3.5f, 3));
    }
    /// <summary>
    /// Test the lastIndexOf method.
    /// </summary>
    TEST_METHOD(MethodLastIndexOf) {
      const float values[] = { 1.5f, 2.5f, 3.5f, 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Check undefined value.
      Assert::AreEqual<Size>(-1, list.lastIndexOf(2.5f, 0));
      Assert::AreEqual<Size>(-1, list.lastIndexOf(0.0f));
      // Check values.
      Assert::AreEqual(0U, list.lastIndexOf(1.5f, 2));
      Assert::AreEqual(1U, list.lastIndexOf(2.5f, 3));
      Assert::AreEqual(2U, list.lastIndexOf(3.5f, 4));
      Assert::AreEqual(3U, list.lastIndexOf(1.5f));
      Assert::AreEqual(4U, list.lastIndexOf(2.5f));
      Assert::AreEqual(5U, list.lastIndexOf(3.5f));
    }
    /// <summary>
    /// Test the contains method.
    /// </summary>
    TEST_METHOD(MethodContains) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Check undefined value.
      Assert::IsFalse(list.contains(0));
      // Check values.
      for (const float& value : values) {
        Assert::IsTrue(list.contains(value));
      }
    }
    /// <summary>
    /// Test the remove method (with return).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReturn) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f });
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&list] {
        Assert::AreEqual(0.0f, list.remove(-1));
      });
      // Remove the second value.
      Assert::AreEqual(2.5f, list.remove(1));
      Assert::AreEqual(2U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsFalse(list.isEmpty());
      Assert::IsFalse(list.contains(2.5f));
      // Remove the third value.
      Assert::AreEqual(3.5f, list.remove(1));
      Assert::AreEqual(1U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsFalse(list.isEmpty());
      Assert::IsFalse(list.contains(3.5f));
      // Remove first value.
      Assert::AreEqual(1.5f, list.remove(0));
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsTrue(list.isEmpty());
      Assert::IsFalse(list.contains(1.5f));
    }
    /// <summary>
    /// Test the remove method (with reference).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReference) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f });
      float value;
      // Check undefined value.
      Assert::IsFalse(list.remove(-1, value));
      // Remove the second value.
      Assert::IsTrue(list.remove(1, value));
      Assert::AreEqual(2.5f, value);
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(2U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsTrue(list.contains(1.5f));
      Assert::IsFalse(list.contains(2.5f));
      Assert::IsTrue(list.contains(3.5f));
      // Remove the third value.
      Assert::IsTrue(list.remove(1, value));
      Assert::AreEqual(3.5f, value);
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(1U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsTrue(list.contains(1.5f));
      Assert::IsFalse(list.contains(2.5f));
      Assert::IsFalse(list.contains(3.5f));
      // Remove the first value.
      Assert::IsTrue(list.remove(0, value));
      Assert::AreEqual(1.5f, value);
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsFalse(list.contains(1.5f));
      Assert::IsFalse(list.contains(2.5f));
      Assert::IsFalse(list.contains(3.5f));
    }
    /// <summary>
    /// Test the remove method (with value).
    /// </summary>
    TEST_METHOD(MethodRemoveWithValue) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f });
      float value;
      // Check undefined value.
      value = 0.0f;
      Assert::IsFalse(list.remove(value));
      // Remove the second value.
      value = 2.5f;
      Assert::IsTrue(list.remove(value));
      Assert::AreEqual(2U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsFalse(list.isEmpty());
      Assert::IsFalse(list.contains(2.5f));
      // Remove the third value.
      value = 3.5f;
      Assert::IsTrue(list.remove(value));
      Assert::AreEqual(1U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsFalse(list.isEmpty());
      Assert::IsFalse(list.contains(3.5f));
      // Remove the first value.
      value = 1.5f;
      Assert::IsTrue(list.remove(value));
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      Assert::IsTrue(list.isEmpty());
      Assert::IsFalse(list.contains(1.5f));
    }
    /// <summary>
    /// Test the slice method.
    /// </summary>
    TEST_METHOD(MethodSlice) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f });
      // Check undefined index.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&list] {
        list.slice(3);
      });
      // Check first part.
      auto part1 = list.slice(0, 1);
      Assert::AreEqual(1U, part1->getLength());
      Assert::AreEqual(part1->get(0), list[0]);
      // Check second part.
      auto part2 = list.slice(1);
      Assert::AreEqual(2U, part2->getLength());
      Assert::AreEqual(part2->get(0), list[1]);
      Assert::AreEqual(part2->get(1), list[2]);
      // Check third part.
      auto part3 = list.slice(2);
      Assert::AreEqual(1U, part3->getLength());
      Assert::AreEqual(part3->get(0), list[2]);
    }
    /// <summary>
    /// Test the sort method.
    /// </summary>
    TEST_METHOD(MethodSort) {
      const float values[] = { 3.5f, 1.5f, 4.5f, 0.5f, 2.5f };
      ArrayList<const float> list(values);
      // Sort data.
      list.sort();
      // Check values.
      const float result[] = { 0.5f, 1.5f, 2.5f, 3.5f, 4.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list[index]);
      }
    }
    /// <summary>
    /// Test the reverse method.
    /// </summary>
    TEST_METHOD(MethodReverse) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Reverse data.
      list.reverse();
      // Check values.
      const float result[] = { 3.5f, 2.5f, 1.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list[index]);
      }
    }
    /// <summary>
    /// Test the clear method.
    /// </summary>
    TEST_METHOD(MethodClear) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      // Clear data.
      list.clear();
      // Check new state.
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      // Check values.
      for (const float& value : values) {
        Assert::IsFalse(list.contains(value));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values), other;
      // Copy list to other.
      other = list;
      // Check copy state.
      Assert::AreEqual(list.isEmpty(), other.isEmpty());
      Assert::AreEqual(list.getLength(), other.getLength());
      Assert::AreEqual(list.getCapacity(), other.getCapacity());
      // Check copy values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(list.get(index), other.get(index));
      }
      // Change values.
      list.set(0, 1.0f);
      list.set(2, 3.0f);
      // Check other values.
      Assert::AreNotEqual(list.get(0), other.get(0));
      Assert::AreEqual(list.get(1), other.get(1));
      Assert::AreNotEqual(list.get(2), other.get(2));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values), other;
      // Move list to other.
      other = Move(list);
      // Check list state.
      Assert::IsTrue(list.isEmpty());
      Assert::AreEqual(0U, list.getLength());
      Assert::AreEqual(0U, list.getCapacity());
      // Check list values.
      for (const float& value : values) {
        Assert::IsFalse(list.contains(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getLength());
      Assert::AreEqual(4U, other.getCapacity());
      // Check other values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(values[index], other.get(index));
      }
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccessConstant) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      ArrayList<const float> list(values);
      const ArrayList<const float> other(list);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&other] {
        Assert::AreEqual(0.0f, other[-1]);
      });
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(float)); ++index) {
        Assert::AreEqual(values[index], other[index]);
      }
    }
    /// <summary>
    /// Test the enlarge capacity feature.
    /// </summary>
    TEST_METHOD(FeatureEnlarge) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f, 4.5f });
      // Check state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(4U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      // Check enlargement.
      list.add(5.5f);
      // Check new state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(5U, list.getLength());
      Assert::AreEqual(8U, list.getCapacity());
      // Check values.
      const float result[] = { 1.5f, 2.5f, 3.5f, 4.5f, 5.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list[index]);
      }
    }
    /// <summary>
    /// Test the shrink capacity feature.
    /// </summary>
    TEST_METHOD(FeatureShrink) {
      ArrayList<const float> list({ 1.5f, 2.5f, 3.5f, 4.5f, 5.5f });
      // Check state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(5U, list.getLength());
      Assert::AreEqual(8U, list.getCapacity());
      // Check shrinkage.
      list.remove(0);
      list.remove(1);
      list.remove(2);
      // Check new state.
      Assert::IsFalse(list.isEmpty());
      Assert::AreEqual(2U, list.getLength());
      Assert::AreEqual(4U, list.getCapacity());
      // Check values.
      const float result[] = { 2.5f, 4.5f };
      for (Index index = 0; index < (sizeof(result) / sizeof(float)); ++index) {
        Assert::AreEqual(result[index], list[index]);
      }
    }
  };
}
