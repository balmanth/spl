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
  TEST_CLASS(AnsiStringTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      AnsiString string;
      // Check state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with length).
    /// </summary>
    TEST_METHOD(ConstructInitializedLength) {
      AnsiString string(3U);
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with string).
    /// </summary>
    TEST_METHOD(ConstructInitializedString) {
      AnsiString string("abc");
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the initialized constructor (with pointer and length).
    /// </summary>
    TEST_METHOD(ConstructInitializedPointer) {
      const char input[] = "abc";
      AnsiString string(input, sizeof(input) - 1);
      // Check state.
      Assert::IsFalse(string.isEmpty());
      Assert::AreEqual(3U, string.getLength());
    }
    /// <summary>
    /// Test the copy constructor.
    /// </summary>
    TEST_METHOD(ConstructCopy) {
      AnsiString string("abc"), other(string);
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
      const char text[] = "abc";
      AnsiString string(text), other(Move(string));
      // Check string state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
      // Check other state.
      Assert::AreEqual(0, other.compare(AnsiString(text)));
    }
    /// <summary>
    /// Test the concat method.
    /// </summary>
    TEST_METHOD(MethodConcat) {
      AnsiString inputA("abc");
      AnsiString inputB("def");
      // Merge values.
      Unique<String<char>> string = inputA.concat({ inputB, AnsiString("ghi") });
      // Check values.
      Assert::AreEqual(0, string->compare(AnsiString("abcdefghi")));
    }
    /// <summary>
    /// Test the get method (by iterator).
    /// </summary>
    TEST_METHOD(MethodGetIterator) {
      const char text[] = "abc";
      AnsiString string(text);
      // Check values.
      auto iterator = string.getIterator();
      for (Index index = 0; iterator->hasNext(); ++index) {
        Assert::AreEqual(iterator->next(), text[index]);
      }
    }
    /// <summary>
    /// Test the indexOf method.
    /// </summary>
    TEST_METHOD(MethodIndexOf) {
      AnsiString string("abcdefabcdef");
      // Check undefined value.
      Assert::AreEqual<Size>(-1, string.indexOf(AnsiString("def"), string.getLength() - 1));
      Assert::AreEqual<Size>(-1, string.indexOf(AnsiString("zzz")));
      Assert::AreEqual<Size>(-1, string.indexOf(AnsiString()));
      // Check defined.
      Assert::AreEqual(0U, string.indexOf(AnsiString("abc")));
      Assert::AreEqual(3U, string.indexOf(AnsiString("def")));
      Assert::AreEqual(6U, string.indexOf(AnsiString("abc"), 3));
      Assert::AreEqual(9U, string.indexOf(AnsiString("def"), 4));
    }
    /// <summary>
    /// Test the lastIndexOf method.
    /// </summary>
    TEST_METHOD(MethodLastIndexOf) {
      AnsiString string("abcdefabcdef");
      // Check undefined value.
      Assert::AreEqual<Size>(-1, string.lastIndexOf(AnsiString("def"), 0));
      Assert::AreEqual<Size>(-1, string.lastIndexOf(AnsiString("zzz")));
      Assert::AreEqual<Size>(-1, string.lastIndexOf(AnsiString()));
      // Check defined.
      Assert::AreEqual(6U, string.lastIndexOf(AnsiString("abc")));
      Assert::AreEqual(9U, string.lastIndexOf(AnsiString("def")));
      Assert::AreEqual(0U, string.lastIndexOf(AnsiString("abc"), string.getLength() - 7));
      Assert::AreEqual(3U, string.lastIndexOf(AnsiString("def"), string.getLength() - 4));
    }
    /// <summary>
    /// Test the contains method.
    /// </summary>
    TEST_METHOD(MethodContains) {
      AnsiString string("abcdefabcdef");
      // Check undefined value.
      Assert::IsFalse(string.contains(AnsiString("zzz")));
      // Check values.
      Assert::IsTrue(string.contains(AnsiString("def")));
    }
    /// <summary>
    /// Test the startsWith method.
    /// </summary>
    TEST_METHOD(MethodStartsWith) {
      AnsiString string("abcdef");
      // Check undefined value.
      Assert::IsFalse(string.startsWith(AnsiString("zzz")));
      // Check values.
      Assert::IsTrue(string.startsWith(AnsiString("abc")));
    }
    /// <summary>
    /// Test the endsWith method.
    /// </summary>
    TEST_METHOD(MethodEndsWith) {
      AnsiString string("abcdef");
      // Check undefined value.
      Assert::IsFalse(string.endsWith(AnsiString("zzz")));
      // Check values.
      Assert::IsTrue(string.endsWith(AnsiString("def")));
    }
    /// <summary>
    /// Test the compare method.
    /// </summary>
    TEST_METHOD(MethodCompare) {
      AnsiString string("abc");
      // Check equality.
      Assert::AreEqual(0, string.compare(AnsiString("abc")));
      Assert::AreEqual(0, string.compare(AnsiString("bc"), 1));
      Assert::AreEqual(0, string.compare(AnsiString("b"), 1, 2));
      Assert::AreEqual(0, string.compare(AnsiString("c"), 2));
      // Check less than.
      Assert::AreEqual(-1, string.compare(AnsiString("bcd")));
      Assert::AreEqual(-1, string.compare(AnsiString("abcd")));
      // Check greater than.
      Assert::AreEqual(1, string.compare(AnsiString("ab")));
      Assert::AreEqual(1, string.compare(AnsiString("aba")));
    }
    /// <summary>
    /// Test the slice method.
    /// </summary>
    TEST_METHOD(MethodSlice) {
      AnsiString string("abc");
      // Check undefined index.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&string] {
        string.slice(3);
      });
      // Check first part.
      Unique<String<char>> part1 = string.slice(0, 1);
      Assert::AreEqual(0, part1->compare(AnsiString("a")));
      // Check second part.
      Unique<String<char>> part2 = string.slice(1);
      Assert::AreEqual(0, part2->compare(AnsiString("bc")));
      // Check third part.
      Unique<String<char>> part3 = string.slice(2);
      Assert::AreEqual(0, part3->compare(AnsiString("c")));
    }
    /// <summary>
    /// Test the reverse method.
    /// </summary>
    TEST_METHOD(MethodReverse) {
      AnsiString string("abc");
      // Reverse data.
      string.reverse();
      // Check values.
      Assert::AreEqual(0, string.compare(AnsiString("cba")));
    }
    /// <summary>
    /// Test the copy assignment operator.
    /// </summary>
    TEST_METHOD(OperatorCopy) {
      AnsiString string("abc"), other;
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
      const char values[] = "abc";
      AnsiString string(values), other;
      // Move string to other.
      other = Move(string);
      // Check string state.
      Assert::IsTrue(string.isEmpty());
      Assert::AreEqual(0U, string.getLength());
      // Check other state.
      Assert::AreEqual(0, other.compare(AnsiString(values)));
    }
    /// <summary>
    /// Test the constant access operator.
    /// </summary>
    TEST_METHOD(OperatorAccessConstant) {
      const char values[] = { 'a','b','c' };
      AnsiString string(values);
      const AnsiString other(string);
      // Check undefined value.
      Assert::ExpectException<SPL::Exceptions::IndexOutOfBounds>([&other] {
        Assert::AreEqual('\0', other[-1]);
      });
      // Check values.
      for (Index index = 0; index < (sizeof(values) / sizeof(char)); ++index) {
        Assert::AreEqual(values[index], other[index]);
      }
    }
  };
}
