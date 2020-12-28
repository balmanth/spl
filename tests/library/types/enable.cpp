/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "metadata.hpp"
#include "types.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Types::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(EnableTests)
  {
  private:
    /// <summary>
    /// Test class.
    /// </summary>
    /// <typeparam name="T">Value type.</typeparam>
    template<typename T>
    class Test final {
    public:
      /// <summary>
      /// Enabled for integer types.
      /// </summary>
      /// <param name="value">Input value.</param>
      /// <returns>Returns the input value multiplied by 2</returns>
      template<typename T = T>
      static EnableType<Metadata::IsInteger<T>, T> run(const T& value) {
        return value * 2;
      }
      /// <summary>
      /// Enabled for decimal types.
      /// </summary>
      /// <param name="value">Input value.</param>
      /// <returns>Returns the input value multiplied by 1.5</returns>
      template<typename T = T>
      static EnableType<Metadata::IsDecimal<T>, T> run(const T& value) {
        return value * 1.5f;
      }
    };
  public:
    /// <summary>
    /// Test the state property.
    /// </summary>
    TEST_METHOD(PropertyState) {
      // Use the integer signature.
      Assert::AreEqual(20, Test<int>::run(10));
      // Use the decimal signature.
      Assert::AreEqual(15.0f, Test<float>::run(10.0f));
    }
  };
}
