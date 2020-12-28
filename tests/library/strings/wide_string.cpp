/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "../mock.hpp"
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "strings.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SPL::Tests;

namespace SPL::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(WideStringTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      WideString string;
      // Check state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with length).
    /// </summary>
    TEST_METHOD(ConstructInitializedLength) {
      WideString string(3U);
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with string).
    /// </summary>
    TEST_METHOD(ConstructInitializedString) {
      WideString string(L"abc");
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with pointer and length).
    /// </summary>
    TEST_METHOD(ConstructInitializedPointer) {
      const wchar_t input[] = L"abc";
      WideString string(input, (sizeof(input) / sizeof(wchar_t)) - 1);
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      WideString string(L"abc"), other(string);
      // Check copy state.
      Assert::AreEqual(0, string.compare(other));
      // Change values.
      string[0] = 'e';
      string[2] = 'f';
      // Check other values.
      Assert::AreNotEqual(0, other.compare(string));
    }
    /// <summary>
    /// Test the move constructor.
    /// </summary>
    TEST_METHOD(ConstructMove) {
      const wchar_t text[] = L"abc";
      WideString string(text), other(Move(string));
      // Check string state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
      // Check other state.
      Assert::AreEqual(0, other.compare(WideString(text)));
    }
    /// <summary>
    /// Test the concat method.
    /// </summary>
    TEST_METHOD(MethodConcat) {
      WideString inputA(L"abc");
      WideString inputB(L"def");
      // Merge values.
      Unique<String<wchar_t>> string = inputA.concat({ inputB, WideString(L"ghi") });
      // Check values.
      Assert::AreEqual(0, string->compare(WideString(L"abcdefghi")));
    }
    /// <summary>
    /// Test the get method (by iterator).
    /// </summary>
    TEST_METHOD(MethodGetIterator) {
      const wchar_t text[] = L"abc";
      WideString string(text);
      // Check values.
      auto iterator = string.getIterator();
      for (Index index = 0; iterator->hasNext(); ++index) {
        Assert::AreEqual<wchar_t>(iterator->next(), text[index]);
      }
    }
    /// <summary>
    /// Test the indexOf method.
    /// </summary>
    TEST_METHOD(MethodIndexOf) {
      WideString string(L"abcdefabcdef");
      // Check undefined value.
      Assert::AreEqual<Size>(-1, string.indexOf(WideString(L"def"), string.getLength() - 1));
      Assert::AreEqual<Size>(-1, string.indexOf(WideString(L"zzz")));
      Assert::AreEqual<Size>(-1, string.indexOf(WideString()));
      // Check defined.
      Assert::AreEqual(0U, string.indexOf(WideString(L"abc")));
      Assert::AreEqual(3U, string.indexOf(WideString(L"def")));
      Assert::AreEqual(6U, string.indexOf(WideString(L"abc"), 3));
      Assert::AreEqual(9U, string.indexOf(WideString(L"def"), 4));
    }
    /// <summary>
    /// Test the lastIndexOf method.
    /// </summary>
    TEST_METHOD(MethodLastIndexOf) {
      WideString string(L"abcdefabcdef");
      // Check undefined value.
      Assert::AreEqual<Size>(-1, string.lastIndexOf(WideString(L"def"), 0));
      Assert::AreEqual<Size>(-1, string.lastIndexOf(WideString(L"zzz")));
      Assert::AreEqual<Size>(-1, string.lastIndexOf(WideString()));
      // Check defined.
      Assert::AreEqual(6U, string.lastIndexOf(WideString(L"abc")));
      Assert::AreEqual(9U, string.lastIndexOf(WideString(L"def")));
      Assert::AreEqual(0U, string.lastIndexOf(WideString(L"abc"), string.getLength() - 7));
      Assert::AreEqual(3U, string.lastIndexOf(WideString(L"def"), string.getLength() - 4));
    }
    /// <summary>
    /// Test the contains method.
    /// </summary>
    TEST_METHOD(MethodContains) {
      WideString string(L"abcdefabcdef");
      // Check undefined value.
      Assert::IsFalse(string.contains(WideString(L"zzz")));
      // Check values.
      Assert::IsTrue(string.contains(WideString(L"def")));
    }
    /// <summary>
    /// Test the startsWith method.
    /// </summary>
    TEST_METHOD(MethodStartsWith) {
      WideString string(L"abcdef");
      // Check undefined value.
      Assert::IsFalse(string.startsWith(WideString(L"zzz")));
      // Check values.
      Assert::IsTrue(string.startsWith(WideString(L"abc")));
    }
    /// <summary>
    /// Test the endsWith method.
    /// </summary>
    TEST_METHOD(MethodEndsWith) {
      WideString string(L"abcdef");
      // Check undefined value.
      Assert::IsFalse(string.endsWith(WideString(L"zzz")));
      // Check values.
      Assert::IsTrue(string.endsWith(WideString(L"def")));
    }
    /// <summary>
    /// Test the compare method.
    /// </summary>
    TEST_METHOD(MethodCompare) {
      WideString string(L"abc");
      // Check equality.
      Assert::AreEqual(0, string.compare(WideString(L"abc")));
      Assert::AreEqual(0, string.compare(WideString(L"bc"), 1));
      Assert::AreEqual(0, string.compare(WideString(L"b"), 1, 2));
      Assert::AreEqual(0, string.compare(WideString(L"c"), 2));
      // Check less than.
      Assert::AreEqual(-1, string.compare(WideString(L"bcd")));
      Assert::AreEqual(-1, string.compare(WideString(L"abcd")));
      // Check greater than.
      Assert::AreEqual(1, string.compare(WideString(L"ab")));
      Assert::AreEqual(1, string.compare(WideString(L"aba")));
    }
    /// <summary>
    /// Test the slice method.
    /// </summary>
    TEST_METHOD(MethodSlice) {
      WideString string(L"abc");
      // Check undefined index.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&string] {
        string.slice(3);
      });
      // Check first part.
      Unique<String<wchar_t>> part1 = string.slice(0, 1);
      Assert::AreEqual(0, part1->compare(WideString(L"a")));
      // Check second part.
      Unique<String<wchar_t>> part2 = string.slice(1);
      Assert::AreEqual(0, part2->compare(WideString(L"bc")));
      // Check third part.
      Unique<String<wchar_t>> part3 = string.slice(2);
      Assert::AreEqual(0, part3->compare(WideString(L"c")));
    }
    /// <summary>
    /// Test the reverse method.
    /// </summary>
    TEST_METHOD(MethodReverse) {
      WideString string(L"abc");
      // Reverse data.
      string.reverse();
      // Check values.
      Assert::AreEqual(0, string.compare(WideString(L"cba")));
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      WideString string(L"abc"), other;
      // Copy string to other.
      other = string;
      // Check copy state.
      Assert::AreEqual(0, string.compare(other));
      // Change values.
      string[0] = 'e';
      string[2] = 'f';
      // Check other values.
      Assert::AreNotEqual(0, other.compare(string));
    }
    /// <summary>
    /// Test the move assignment operator.
    /// </summary>
    TEST_METHOD(OperatorMove) {
      const wchar_t values[] = L"abc";
      WideString string(values), other;
      // Move string to other.
      other = Move(string);
      // Check string state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
      // Check other state.
      Assert::AreEqual(0, other.compare(WideString(values)));
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccessConstant) {
      const wchar_t values[] = { 'a','b','c' };
      WideString string(values);
      const WideString other(string);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&other] {
        Assert::AreEqual<wchar_t>('\0', other[-1]);
      });
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(wchar_t)); ++index) {
        Assert::AreEqual(values[index], other[index]);
      }
    }
  };
}
