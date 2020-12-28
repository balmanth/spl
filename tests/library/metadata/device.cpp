/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "metadata.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SPL::Metadata::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(DeviceTests)
  {
  public:
    /// <summary>
    /// Test the 'Version' property.
    /// </summary>
    TEST_METHOD(PropertyVersion) {
#if defined(WIN32)
      Assert::AreEqual(32, Device::Bit);
      Assert::IsTrue(Device::x86);
#else
      Assert::AreEqual(64, Device::Bit);
      Assert::IsTrue(Device::x64);
#endif
    }
  };
}
