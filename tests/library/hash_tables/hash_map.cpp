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
  TEST_CLASS(HashMapTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      HashMap<const char*, float> map;
      // Check state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(0U, map.getCapacity());
      Assert::AreEqual(1.0f, map.getLoadFactor());
    }
    /// <summary>
    /// Test the capacity constructor.
    /// </summary>
    TEST_METHOD(ConstructCapacity) {
      HashMap<const char*, float> map(8);
      // Check state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(8U, map.getCapacity());
      Assert::AreEqual(0.0f, map.getLoadFactor());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructPairs) {
      HashMap<const char*, float> map({ { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs), other(map);
      // Check copy state.
      Assert::AreEqual(map.isEmpty(), other.isEmpty());
      Assert::AreEqual(map.getSize(), other.getSize());
      Assert::AreEqual(map.getCapacity(), other.getCapacity());
      Assert::AreEqual(map.getLoadFactor(), other.getLoadFactor());
      // Check copy values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(map.get(pair.key), other.get(pair.key));
      }
      // Change values.
      map.set("abc", 10.5f);
      map.set("ghi", 30.5f);
      // Check other values.
      Assert::AreNotEqual(map.get("abc"), other.get("abc"));
      Assert::AreEqual(map.get("def"), other.get("def"));
      Assert::AreNotEqual(map.get("ghi"), other.get("ghi"));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs), other(Move(map));
      // Check map state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(0U, map.getCapacity());
      Assert::AreEqual(1.0f, map.getLoadFactor());
      // Check map values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getSize());
      Assert::AreEqual(4U, other.getCapacity());
      Assert::AreEqual(0.75f, other.getLoadFactor());
      // Check other values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(pair.value, other.get(pair.key));
      }
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      Size instances = 0;
      // Create a new instance.
      SPL::Map<const char*, Mock>* map = new HashMap<const char*, Mock>({
          { "abc", Mock(instances) },
          { "def", Mock(instances) },
          { "ghi", Mock(instances) }
        });
      Assert::AreEqual(3U, instances);
      // Delete the instance.
      delete map;
      // Check state.
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the set method.
    /// </summary>
    TEST_METHOD(MethodSet) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Map new values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(pair.value, map.set(pair.key, pair.value + 0.5f));
      }
      Assert::AreEqual(0.0f, map.set("jkl", 5.0f));
      // Check new state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      Assert::AreEqual(8U, map.getCapacity());
      Assert::AreEqual(0.5f, map.getLoadFactor());
      // Check new values.
      const Pair<const char*, float> result[] = { { "abc", 2.0f }, { "def", 3.0f }, { "ghi", 4.0f}, { "jkl", 5.0f} };
      for (const Pair<const char*, float>& pair : result) {
        Assert::AreEqual(pair.value, map.get(pair.key));
      }
    }
    /// <summary>
    /// Test the get method (by return).
    /// </summary>
    TEST_METHOD(MethodGetByReturn) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0.0f, map.get(nullptr));
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0.0f, map.get("cba"));
      });
      // Check values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(pair.value, map.get(pair.key));
      }
    }
    /// <summary>
    /// Test the get method (by reference).
    /// </summary>
    TEST_METHOD(MethodGetByReference) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      float value;
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check undefined value.
      Assert::IsFalse(map.get(nullptr, value));
      Assert::IsFalse(map.get("cba", value));
      // Check values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::IsTrue(map.get(pair.key, value));
        Assert::AreEqual(pair.value, value);
      }
    }
    /// <summary>
    /// Test the get method (by iterator).
    /// </summary>
    TEST_METHOD(MethodGetByIterator) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      // Check values in the hash order.
      auto iterator = map.getIterator();
      const Pair<const char*, float> result[] = { { "ghi", 3.5f }, { "def", 2.5f }, { "abc", 1.5f } };
      for (Index index = 0; iterator->hasNext(); ++index) {
        const auto& current = iterator->next();
        Assert::AreEqual(result[index].key, current.getKey());
        Assert::AreEqual(result[index].value, current.value);
      }
    }
    /// <summary>
    /// Test the has method.
    /// </summary>
    TEST_METHOD(MethodHas) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check undefined value.
      Assert::IsFalse(map.has(nullptr));
      Assert::IsFalse(map.has("cba"));
      // Check values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::IsTrue(map.has(pair.key));
      }
    }
    /// <summary>
    /// Test the remove method (with return).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReturn) {
      HashMap<const char*, float> map({ { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0.0f, map.remove(nullptr));
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0.0f, map.remove("cba"));
      });
      // Remove the second value.
      Assert::AreEqual(2.5f, map.remove("def"));
      Assert::AreEqual(2U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.5f, map.getLoadFactor());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("def"));
      // Remove the third value.
      Assert::AreEqual(3.5f, map.remove("ghi"));
      Assert::AreEqual(1U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.25f, map.getLoadFactor());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("ghi"));
      // Remove first value.
      Assert::AreEqual(1.5f, map.remove("abc"));
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.0f, map.getLoadFactor());
      Assert::IsTrue(map.isEmpty());
      Assert::IsFalse(map.has("abc"));
    }
    /// <summary>
    /// Test the remove method (with reference).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReference) {
      HashMap<const char*, float> map({ { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } });
      float value;
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check undefined value.
      Assert::IsFalse(map.remove(nullptr, value));
      Assert::IsFalse(map.remove("cba", value));
      // Remove the second value.
      Assert::IsTrue(map.remove("def", value));
      Assert::AreEqual(2.5f, value);
      Assert::AreEqual(2U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.5f, map.getLoadFactor());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("def"));
      // Remove the third value.
      Assert::IsTrue(map.remove("ghi", value));
      Assert::AreEqual(3.5f, value);
      Assert::AreEqual(1U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.25f, map.getLoadFactor());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("ghi"));
      // Remove the first value.
      Assert::IsTrue(map.remove("abc", value));
      Assert::AreEqual(1.5f, value);
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.0f, map.getLoadFactor());
      Assert::IsTrue(map.isEmpty());
      Assert::IsFalse(map.has("abc"));
    }
    /// <summary>
    /// Test the clear method.
    /// </summary>
    TEST_METHOD(MethodClear) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Clear data.
      map.clear();
      // Check new state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.0f, map.getLoadFactor());
      // Check values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs), other;
      // Copy map to other.
      other = map;
      // Check copy state.
      Assert::AreEqual(map.isEmpty(), other.isEmpty());
      Assert::AreEqual(map.getSize(), other.getSize());
      Assert::AreEqual(map.getCapacity(), other.getCapacity());
      Assert::AreEqual(map.getLoadFactor(), other.getLoadFactor());
      // Check copy values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(map[pair.key], other[pair.key]);
      }
      // Change values.
      map.set("abc", 10.5f);
      map.set("ghi", 30.5f);
      // Check other values.
      Assert::AreNotEqual(map.get("abc"), other.get("abc"));
      Assert::AreEqual(map.get("def"), other.get("def"));
      Assert::AreNotEqual(map.get("ghi"), other.get("ghi"));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs), other;
      // Move map to other.
      other = Move(map);
      // Check map state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(0U, map.getCapacity());
      Assert::AreEqual(1.0f, map.getLoadFactor());
      // Check map values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(3U, other.getSize());
      Assert::AreEqual(4U, other.getCapacity());
      Assert::AreEqual(0.75f, other.getLoadFactor());
      // Check other values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(pair.value, other[pair.key]);
      }
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccessConstant) {
      const Pair<const char*, float> pairs[] = { { "abc", 1.5f }, { "def", 2.5f }, { "ghi", 3.5f } };
      HashMap<const char*, float> map(pairs);
      const HashMap<const char*, float> other(map);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&other] {
        Assert::AreEqual(0.0f, other[nullptr]);
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&other] {
        Assert::AreEqual(0.0f, other["cba"]);
      });
      // Check values.
      for (const Pair<const char*, float>& pair : pairs) {
        Assert::AreEqual(pair.value, other[pair.key]);
      }
    }
    /// <summary>
    /// Test the enlarge capacity feature.
    /// </summary>
    TEST_METHOD(FeatureEnlarge) {
      HashMap<const char*, float> map({
          { "abc", 1.5f },
          { "def", 2.5f },
          { "ghi", 3.5f },
          { "jkl", 4.5f },
          { "mno", 5.5f },
          { "pqr", 6.5f }
        });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(6U, map.getSize());
      Assert::AreEqual(8U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check enlargement.
      map.set("stu", 7.5f);
      // Check new state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(7U, map.getSize());
      Assert::AreEqual(16U, map.getCapacity());
      Assert::AreEqual(0.4375f, map.getLoadFactor());
      // Check values.
      const Pair<const char*, float> result[] = {
        { "abc", 1.5f },
        { "def", 2.5f },
        { "ghi", 3.5f },
        { "jkl", 4.5f },
        { "mno", 5.5f },
        { "pqr", 6.5f },
        { "stu", 7.5f }
      };
      for (const Pair<const char*, float>& pair : result) {
        Assert::AreEqual(pair.value, map[pair.key]);
      }
    }
    /// <summary>
    /// Test the shrink capacity feature.
    /// </summary>
    TEST_METHOD(FeatureShrink) {
      HashMap<const char*, float> map({
          { "abc", 1.5f },
          { "def", 2.5f },
          { "ghi", 3.5f },
          { "jkl", 4.5f },
          { "mno", 5.5f },
          { "pqr", 6.5f },
          { "stu", 7.5f }
        });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(7U, map.getSize());
      Assert::AreEqual(16U, map.getCapacity());
      Assert::AreEqual(0.4375f, map.getLoadFactor());
      // Check shrinkage.
      map.remove("def");
      map.remove("jkl");
      map.remove("pqr");
      // Check new state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      Assert::AreEqual(8U, map.getCapacity());
      Assert::AreEqual(0.5f, map.getLoadFactor());
      // Check values.
      const Pair<const char*, float> result[] = {
        { "abc", 1.5f },
        { "ghi", 3.5f },
        { "mno", 5.5f },
        { "stu", 7.5f }
      };
      for (const Pair<const char*, float>& pair : result) {
        Assert::AreEqual(pair.value, map[pair.key]);
      }
    }
    /// <summary>
    /// Test the collision resolution feature.
    /// </summary>
    TEST_METHOD(FeatureCollisions) {
      const Pair<const int, float> pairs[] = { { 15, 1.5f }, { 23, 2.3f }, { 31, 3.1f } };
      HashMap<const int, float> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check values.
      for (const Pair<const int, float>& pair : pairs) {
        Assert::AreEqual(pair.value, map[pair.key]);
      }
      // Remove collision.
      map.remove(23);
      // Check values.
      Assert::IsTrue(map.has(15));
      Assert::IsFalse(map.has(23));
      Assert::IsTrue(map.has(31));
      // Reuse free entry.
      map[39] = 3.9f;
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(4U, map.getCapacity());
      Assert::AreEqual(0.75f, map.getLoadFactor());
      // Check values.
      Assert::AreEqual(1.5f, map[15]);
      Assert::AreEqual(3.1f, map[31]);
      Assert::AreEqual(3.9f, map[39]);
    }
  };
}
