/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "prefixtrees.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SPL::Tests;

namespace SPL::PrefixTrees::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(PrefixMapTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      PrefixMap<const char*, int> map;
      // Check state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      PrefixMap<const char*, int> map({ { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs), other(map);
      // Check copy state.
      Assert::AreEqual(map.isEmpty(), other.isEmpty());
      Assert::AreEqual(map.getSize(), other.getSize());
      // Check copy values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(map.get(pair.key), other.get(pair.key));
      }
      // Change values.
      map.set("abc", 100);
      map.set("acd", 300);
      // Check other values.
      Assert::AreNotEqual(map.get("abc"), other.get("abc"));
      Assert::AreEqual(map.get("aab"), other.get("aab"));
      Assert::AreNotEqual(map.get("acd"), other.get("acd"));
      Assert::AreEqual(map.get("aa"), other.get("aa"));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs), other(Move(map));
      // Check map state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      // Check map values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(4U, other.getSize());
      // Check other values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(pair.value, other.get(pair.key));
      }
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      Size instances = 0;
      // Create a new instance.
      SPL::Map<const char*, Mock>* map = new PrefixMap<const char*, Mock>({
          { "abc", Mock(instances) },
          { "aab", Mock(instances) },
          { "acd", Mock(instances) },
          { "aa",  Mock(instances) }
        });
      Assert::AreEqual(4U, instances);
      // Delete the instance.
      delete map;
      Assert::AreEqual(0U, instances);
    }
    /// <summary>
    /// Test the set method.
    /// </summary>
    TEST_METHOD(MethodSet) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Map invalid key.
      Assert::ExpectException<SPL::Exceptions::InvalidArgument>([&map] {
        Assert::AreEqual(0, map.set(nullptr, 1000));
      });
      // Map new values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(pair.value, map.set(pair.key, pair.value + 5));
      }
      Assert::AreEqual(0, map.set("abcd", 45));
      // Check new state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(5U, map.getSize());
      // Check new values.
      const Pair<const char*, int> result[] = { { "abc", 15 }, { "aab", 25 }, { "acd", 35 }, { "aa", 45 }, {"abcd", 45} };
      for (const Pair<const char*, int>& pair : result) {
        Assert::AreEqual(pair.value, map.get(pair.key));
      }
    }
    /// <summary>
    /// Test the get method (by return).
    /// </summary>
    TEST_METHOD(MethodGetByReturn) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0, map.get(nullptr));
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0, map.get("cba"));
      });
      // Check values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(pair.value, map.get(pair.key));
      }
    }
    /// <summary>
    /// Test the get method (by reference).
    /// </summary>
    TEST_METHOD(MethodGetByReference) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      int value;
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Check undefined value.
      Assert::IsFalse(map.get(nullptr, value));
      Assert::IsFalse(map.get("cba", value));
      // Check values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::IsTrue(map.get(pair.key, value));
        Assert::AreEqual(pair.value, value);
      }
    }
    /// <summary>
    /// Test the has method.
    /// </summary>
    TEST_METHOD(MethodHas) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Check undefined value.
      Assert::IsFalse(map.has(nullptr));
      Assert::IsFalse(map.has("cba"));
      // Check values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::IsTrue(map.has(pair.key));
      }
    }
    /// <summary>
    /// Test the remove method (with return).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReturn) {
      PrefixMap<const char*, int> map({ { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } });
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0, map.remove(nullptr));
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&map] {
        Assert::AreEqual(0, map.remove("cba"));
      });
      // Remove the second value.
      Assert::AreEqual(20, map.remove("aab"));
      Assert::AreEqual(3U, map.getSize());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("aab"));
      // Remove the third value.
      Assert::AreEqual(30, map.remove("acd"));
      Assert::AreEqual(2U, map.getSize());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("acd"));
      // Remove first value.
      Assert::AreEqual(10, map.remove("abc"));
      Assert::AreEqual(1U, map.getSize());
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("abc"));
      // Remove fourth value.
      Assert::AreEqual(40, map.remove("aa"));
      Assert::AreEqual(0U, map.getSize());
      Assert::IsTrue(map.isEmpty());
      Assert::IsFalse(map.has("aa"));
    }
    /// <summary>
    /// Test the remove method (with reference).
    /// </summary>
    TEST_METHOD(MethodRemoveWithReference) {
      PrefixMap<const char*, int> map({ { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } });
      int value;
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Check undefined value.
      Assert::IsFalse(map.remove(nullptr, value));
      Assert::IsFalse(map.remove("cba", value));
      // Remove the second value.
      Assert::IsTrue(map.remove("aab", value));
      Assert::AreEqual(3U, map.getSize());
      Assert::AreEqual(20, value);
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("aab"));
      // Remove the third value.
      Assert::IsTrue(map.remove("acd", value));
      Assert::AreEqual(2U, map.getSize());
      Assert::AreEqual(30, value);
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("acd"));
      // Remove the first value.
      Assert::IsTrue(map.remove("abc", value));
      Assert::AreEqual(1U, map.getSize());
      Assert::AreEqual(10, value);
      Assert::IsFalse(map.isEmpty());
      Assert::IsFalse(map.has("abc"));
      // Remove the fourth value.
      Assert::IsTrue(map.remove("aa", value));
      Assert::AreEqual(0U, map.getSize());
      Assert::AreEqual(40, value);
      Assert::IsTrue(map.isEmpty());
      Assert::IsFalse(map.has("aa"));
    }
    /// <summary>
    /// Test the clear method.
    /// </summary>
    TEST_METHOD(MethodClear) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      // Check state.
      Assert::IsFalse(map.isEmpty());
      Assert::AreEqual(4U, map.getSize());
      // Clear data.
      map.clear();
      // Check new state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      // Check values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs), other;
      // Copy map to other.
      other = map;
      // Check copy state.
      Assert::AreEqual(map.isEmpty(), other.isEmpty());
      Assert::AreEqual(map.getSize(), other.getSize());
      // Check copy values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(map[pair.key], other[pair.key]);
      }
      // Change values.
      map.set("abc", 100);
      map.set("acd", 300);
      // Check other values.
      Assert::AreNotEqual(map.get("abc"), other.get("abc"));
      Assert::AreEqual(map.get("aab"), other.get("aab"));
      Assert::AreNotEqual(map.get("acd"), other.get("acd"));
      Assert::AreEqual(map.get("aa"), other.get("aa"));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs), other;
      // Move map to other.
      other = Move(map);
      // Check map state.
      Assert::IsTrue(map.isEmpty());
      Assert::AreEqual(0U, map.getSize());
      // Check map values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::IsFalse(map.has(pair.key));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(4U, other.getSize());
      // Check other values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(pair.value, other[pair.key]);
      }
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccessConstant) {
      const Pair<const char*, int> pairs[] = { { "abc", 10 }, { "aab", 20 }, { "acd", 30 }, { "aa", 40 } };
      PrefixMap<const char*, int> map(pairs);
      const PrefixMap<const char*, int> other(map);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&other] {
        Assert::AreEqual(0, other[nullptr]);
      });
      Assert::ExpectException<SPL::Exceptions::KeyNotFound<const char*>>([&other] {
        Assert::AreEqual(0, other["cba"]);
      });
      // Check values.
      for (const Pair<const char*, int>& pair : pairs) {
        Assert::AreEqual(pair.value, other[pair.key]);
      }
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorCastNode) {
      PrefixMap<const char*, int> map({ { "abc", 10 } });
      const Node<const char*, int>* root = map;
      // Check values.
      Assert::AreEqual('a', root->getKey());
      Assert::AreEqual('b', root->getDownNode()->getKey());
      Assert::AreEqual('c', root->getDownNode()->getDownNode()->getKey());
    }
  };
}
