/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../metadata.hpp"
#include "./types.hpp"

namespace SPL {
  template<typename T, Size N>
  class Initializer {
  private:
    const T* entries[N];
  public:

    template<typename ...U, typename Metadata::Enable<Metadata::Compare<T, U...>::State>::Type* = nullptr>
    Initializer(const U& ...entries) :
      entries{ &entries ... } {}

    const T& operator [](const Index index) const override {
      return this->entries[index];
    }
  };

  template<typename T, Size N>
  Initializer(const T(&entries)[N])->Initializer<T, N>;
}
