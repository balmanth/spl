/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "hash_tables.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SPL::Tests;

namespace SPL::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(HashSetTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      HashSet<const float> set;
      // Check state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(0U, set.getCapacity());
      Assert::AreEqual(1.0f, set.getLoadFactor());
    }
    /// <summary>
    /// Test the capacity constructor.
    /// </summary>
    TEST_METHOD(ConstructCapacity) {
      HashSet<const float> set(8);
      // Check state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(8U, set.getCapacity());
      Assert::AreEqual(0.0f, set.getLoadFactor());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructValues) {
      HashSet<const float> set({ 1.5f, 2.5f, 3.5f, 1.5f, 2.5f, 3.5f });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(8U, set.getCapacity());
      Assert::AreEqual(0.375f, set.getLoadFactor());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values), other(set);
      // Check copy state.
      Assert::AreEqual(set.isEmpty(), other.isEmpty());
      Assert::AreEqual(set.getSize(), other.getSize());
      Assert::AreEqual(set.getCapacity(), other.getCapacity());
      Assert::AreEqual(set.getLoadFactor(), other.getLoadFactor());
      // Check copy values.
      for (const float value : values) {
        Assert::AreEqual(set.has(value), other.has(value));
      }
      // Change values.
      set.remove(1.5f);
      set.remove(3.5f);
      // Check other values.
      Assert::AreNotEqual(set.has(1.5f), other.has(1.5f));
      Assert::AreEqual(set.has(2.5f), other.has(2.5f));
      Assert::AreNotEqual(set.has(3.5f), other.has(3.5f));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values), other(Move(set));
      // Check set state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(0U, set.getCapacity());
      Assert::AreEqual(1.0f, set.getLoadFactor());
      // Check set values.
      for (const float value : values) {
        Assert::IsFalse(set.has(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getSize());
      Assert::AreEqual(4U, other.getCapacity());
      Assert::AreEqual(0.75f, other.getLoadFactor());
      // Check other values.
      for (const float value : values) {
        Assert::IsTrue(other.has(value));
      }
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      Size instances = 0;
      // Create a new instance.
      SPL::Set<Mock>* set = new HashSet<Mock>({
          Mock(instances),
          Mock(instances),
          Mock(instances)
        });
      Assert::AreEqual(3U, instances);
      // Delete the instance.
      delete set;
      // Check state.
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the add method.
    /// </summary>
    TEST_METHOD(MethodAdd) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Set new values.
      for (const float value : values) {
        set.add(value);
      }
      set.add(4.5f);
      // Check new state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      Assert::AreEqual(8U, set.getCapacity());
      Assert::AreEqual(0.5f, set.getLoadFactor());
      // Check new values.
      const float result[] = { 1.5f, 2.5f, 3.5f, 4.5f };
      for (const float value : result) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the get method (by iterator).
    /// </summary>
    TEST_METHOD(MethodGetIterator) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values);
      // Check values in the hash order.
      auto iterator = set.getIterator();
      const float result[] = { 1.5f, 2.5f, 3.5f };
      for (Index index = 0; iterator->hasNext(); ++index) {
        const auto& current = iterator->next();
        Assert::AreEqual(result[index], current.getKey());
      }
    }
    /// <summary>
    /// Test the has method.
    /// </summary>
    TEST_METHOD(MethodHas) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Check undefined value.
      Assert::IsFalse(set.has(0));
      // Check values.
      for (const float value : values) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the remove method.
    /// </summary>
    TEST_METHOD(MethodRemove) {
      HashSet<const float> set({ 1.5f, 2.5f, 3.5f });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Check undefined values.
      Assert::IsFalse(set.remove(0.0f));
      // Remove the second value.
      Assert::IsTrue(set.remove(2.5f));
      Assert::AreEqual(2U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.5f, set.getLoadFactor());
      Assert::IsFalse(set.isEmpty());
      Assert::IsFalse(set.has(2.5f));
      // Remove the third value.
      Assert::IsTrue(set.remove(3.5f));
      Assert::AreEqual(1U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.25f, set.getLoadFactor());
      Assert::IsFalse(set.isEmpty());
      Assert::IsFalse(set.has(3.5f));
      // Remove the first value.
      Assert::IsTrue(set.remove(1.5f));
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.0f, set.getLoadFactor());
      Assert::IsTrue(set.isEmpty());
      Assert::IsFalse(set.has(1.5f));
    }
    /// <summary>
    /// Test the clear method.
    /// </summary>
    TEST_METHOD(MethodClear) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Clear data.
      set.clear();
      // Check new state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.0f, set.getLoadFactor());
      // Check values.
      for (const float value : values) {
        Assert::IsFalse(set.has(value));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values), other;
      // Copy set to other.
      other = set;
      // Check copy state.
      Assert::AreEqual(set.isEmpty(), other.isEmpty());
      Assert::AreEqual(set.getSize(), other.getSize());
      Assert::AreEqual(set.getCapacity(), other.getCapacity());
      Assert::AreEqual(set.getLoadFactor(), other.getLoadFactor());
      // Check copy values.
      for (const float value : values) {
        Assert::AreEqual(set.has(value), other.has(value));
      }
      // Change values.
      set.remove(1.5f);
      set.remove(3.5f);
      // Check other values.
      Assert::AreNotEqual(set.has(1.5f), other.has(1.5f));
      Assert::AreEqual(set.has(2.5f), other.has(2.5f));
      Assert::AreNotEqual(set.has(3.5f), other.has(3.5f));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const float values[] = { 1.5f, 2.5f, 3.5f };
      HashSet<const float> set(values), other;
      // Move set to other.
      other = Move(set);
      // Check set state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      Assert::AreEqual(0U, set.getCapacity());
      Assert::AreEqual(1.0f, set.getLoadFactor());
      // Check values.
      for (const float value : values) {
        Assert::IsFalse(set.has(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getSize());
      Assert::AreEqual(4U, other.getCapacity());
      Assert::AreEqual(0.75f, other.getLoadFactor());
      // Check other values.
      for (const float value : values) {
        Assert::IsTrue(other.has(value));
      }
    }
    /// <summary>
    /// Test the enlarge capacity feature.
    /// </summary>
    TEST_METHOD(FeatureEnlarge) {
      HashSet<const float> set({ 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(6U, set.getSize());
      Assert::AreEqual(8U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Check enlargement.
      set.add(7.5f);
      // Check new state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(7U, set.getSize());
      Assert::AreEqual(16U, set.getCapacity());
      Assert::AreEqual(0.4375f, set.getLoadFactor());
      // Check values.
      const float result[] = { 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
      for (const float value : result) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the shrink capacity feature.
    /// </summary>
    TEST_METHOD(FeatureShrink) {
      HashSet<const float> set({ 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(7U, set.getSize());
      Assert::AreEqual(16U, set.getCapacity());
      Assert::AreEqual(0.4375f, set.getLoadFactor());
      // Check shrinkage.
      set.remove(2.5f);
      set.remove(4.5f);
      set.remove(6.5f);
      // Check new state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      Assert::AreEqual(8U, set.getCapacity());
      Assert::AreEqual(0.5f, set.getLoadFactor());
      // Check values.
      const float result[] = { 1.5f, 3.5f, 5.5f, 7.5f };
      for (const float value : result) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the collision resolution feature.
    /// </summary>
    TEST_METHOD(FeatureCollision) {
      const float values[] = { 15.5f, 23.5f, 31.5f };
      HashSet<const float> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Check values.
      for (const float value : values) {
        Assert::IsTrue(set.has(value));
      }
      // Remove collision.
      set.remove(23.5f);
      // Check values.
      Assert::IsTrue(set.has(15.5f));
      Assert::IsFalse(set.has(23.5f));
      Assert::IsTrue(set.has(31.5f));
      // Reuse free entry.
      set.add(39.5f);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(3U, set.getSize());
      Assert::AreEqual(4U, set.getCapacity());
      Assert::AreEqual(0.75f, set.getLoadFactor());
      // Check values.
      Assert::IsTrue(set.has(15.5f));
      Assert::IsTrue(set.has(31.5f));
      Assert::IsTrue(set.has(39.5f));
    }
  };
}
