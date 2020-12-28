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
  TEST_CLASS(PrefixSetTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      PrefixSet<const char*> set;
      // Check state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      PrefixSet<const char*> set({ "abc", "aab", "acd", "aa" });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values), other(set);
      // Check copy state.
      Assert::AreEqual(set.isEmpty(), other.isEmpty());
      Assert::AreEqual(set.getSize(), other.getSize());
      // Check copy values.
      for (const char* value : values) {
        Assert::AreEqual(set.has(value), other.has(value));
      }
      // Change values.
      set.remove("abc");
      set.remove("acd");
      // Check other values.
      Assert::AreNotEqual(set.has("abc"), other.has("abc"));
      Assert::AreEqual(set.has("aab"), other.has("aab"));
      Assert::AreNotEqual(set.has("acd"), other.has("acd"));
      Assert::AreEqual(set.has("aa"), other.has("aa"));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values), other(Move(set));
      // Check set state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      // Check set values.
      for (const char* value : values) {
        Assert::IsFalse(set.has(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(4U, other.getSize());
      // Check other values.
      for (const char* value : values) {
        Assert::IsTrue(other.has(value));
      }
    }
    /// <summary>
    /// Test the destructor.
    /// </summary>
    TEST_METHOD(Destruct) {
      /*Size instances = 0;
      // Create a new instance.
      SPL::Set<Mock>* set = new PrefixSet<Mock>({
          Mock(instances),
          Mock(instances),
          Mock(instances)
        });
      Assert::AreEqual(3U, instances);
      // Delete the instance.
      delete set;
      Assert::AreEqual(0U, instances);
      */
    }
    /// <summary>
    /// Test the add method.
    /// </summary>
    TEST_METHOD(MethodAdd) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      // Add invalid value.
      Assert::ExpectException<SPL::Exceptions::InvalidArgument>([&set] {
        set.add(nullptr);
      });
      // Set new values.
      for (const char* value : values) {
        set.add(value);
      }
      set.add("abcd");
      // Check new state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(5U, set.getSize());
      // Check new values.
      const char* result[] = { "abc", "aab", "acd", "aa", "abcd" };
      for (const char* value : result) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the has method.
    /// </summary>
    TEST_METHOD(MethodHas) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      // Check undefined value.
      Assert::IsFalse(set.has(nullptr));
      Assert::IsFalse(set.has("cba"));
      // Check values.
      for (const char* value : values) {
        Assert::IsTrue(set.has(value));
      }
    }
    /// <summary>
    /// Test the remove method.
    /// </summary>
    TEST_METHOD(MethodRemove) {
      PrefixSet<const char*> set({ "abc", "aab", "acd", "aa" });
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      // Check undefined values.
      Assert::IsFalse(set.remove(nullptr));
      Assert::IsFalse(set.remove("cba"));
      // Remove the second value.
      Assert::IsTrue(set.remove("aab"));
      Assert::AreEqual(3U, set.getSize());
      Assert::IsFalse(set.isEmpty());
      Assert::IsFalse(set.has("aab"));
      // Remove the third value.
      Assert::IsTrue(set.remove("acd"));
      Assert::AreEqual(2U, set.getSize());
      Assert::IsFalse(set.isEmpty());
      Assert::IsFalse(set.has("acd"));
      // Remove the first value.
      Assert::IsTrue(set.remove("abc"));
      Assert::AreEqual(1U, set.getSize());
      Assert::IsFalse(set.isEmpty());
      Assert::IsFalse(set.has("abc"));
      // Remove the fourth value.
      Assert::IsTrue(set.remove("aa"));
      Assert::AreEqual(0U, set.getSize());
      Assert::IsTrue(set.isEmpty());
      Assert::IsFalse(set.has("aa"));
    }
    /// <summary>
    /// Test the clear method.
    /// </summary>
    TEST_METHOD(MethodClear) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values);
      // Check state.
      Assert::IsFalse(set.isEmpty());
      Assert::AreEqual(4U, set.getSize());
      // Clear data.
      set.clear();
      // Check new state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      // Check values.
      for (const char* value : values) {
        Assert::IsFalse(set.has(value));
      }
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values), other;
      // Copy set to other.
      other = set;
      // Check copy state.
      Assert::AreEqual(set.isEmpty(), other.isEmpty());
      Assert::AreEqual(set.getSize(), other.getSize());
      // Check copy values.
      for (const char* value : values) {
        Assert::AreEqual(set.has(value), other.has(value));
      }
      // Change values.
      set.remove("abc");
      set.remove("acd");
      // Check other values.
      Assert::AreNotEqual(set.has("abc"), other.has("abc"));
      Assert::AreEqual(set.has("aab"), other.has("aab"));
      Assert::AreNotEqual(set.has("acd"), other.has("acd"));
      Assert::AreEqual(set.has("aa"), other.has("aa"));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const char* values[] = { "abc", "aab", "acd", "aa" };
      PrefixSet<const char*> set(values), other;
      // Move set to other.
      other = Move(set);
      // Check set state.
      Assert::IsTrue(set.isEmpty());
      Assert::AreEqual(0U, set.getSize());
      // Check values.
      for (const char* value : values) {
        Assert::IsFalse(set.has(value));
      }
      // Check other state.
      Assert::IsFalse(other.isEmpty());
      Assert::AreEqual(4U, other.getSize());
      // Check other values.
      for (const char* value : values) {
        Assert::IsTrue(other.has(value));
      }
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorCastNode) {
      PrefixSet<const char*> map({ "abc" });
      const Node<const char*>* root = map;
      // Check values.
      Assert::AreEqual('a', root->getKey());
      Assert::AreEqual('b', root->getDownNode()->getKey());
      Assert::AreEqual('c', root->getDownNode()->getDownNode()->getKey());
    }
  };
}
