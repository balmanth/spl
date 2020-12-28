/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace SPL::Arrays {
  /// <summary>
  /// Basic array class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  class BasicArray final {
  private:
    /// <summary>
    /// Non-constant element type.
    /// </summary>
    using ElementType = Metadata::ConstantType<T>;
    /// <summary>
    /// Total number of elements.
    /// </summary>
    Size capacity;
    /// <summary>
    /// Elements of the array.
    /// </summary>
    ElementType* elements;
    /// <summary>
    /// Current number of elements.
    /// </summary>
    Size length;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(BasicArray& source, BasicArray& target) noexcept {
      using SPL::Swap;
      Swap(source.capacity, target.capacity);
      Swap(source.elements, target.elements);
      Swap(source.length, target.length);
    }
    /// <summary>
    /// Resize the current capacity based on the new one and move all elements.
    /// IMPORTANT: Make sure the new capacity can store all current elements.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    void resize(const Size capacity) {
      using SPL::Swap;
      BasicArray array(capacity);
      while (array.length < this->length) {
        Swap(array.elements[array.length], this->elements[array.length]);
        array.length++;
      }
      this->length = 0;
      Swap(*this, array);
    }
  private:
    /// <summary>
    /// Internal constructor.
    /// </summary>
    /// <param name="elements">Initial elements.</param>
    /// <param name="length">Initial length.</param>
    BasicArray(const T elements[], const Size length) : BasicArray(length) {
      Copy(elements, this->elements, length);
      this->length = length;
    }
  public:
    /// <summary>
    /// Initialized constructor for capacity.
    /// </summary>
    /// <param name="capacity">Initial capacity.</param>
    explicit BasicArray(const Size capacity) :
      capacity(Math::Max(capacity, 4U)), elements(new ElementType[this->capacity]()), length(0) {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    BasicArray() :
      capacity(0), elements(nullptr), length(0) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicArray(const BasicArray& other) :
      BasicArray(other.elements, other.length) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    BasicArray(BasicArray&& other) noexcept : BasicArray() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~BasicArray() {
      delete[] this->elements;
    }
  public:
    /// <summary>
    /// Get the capacity of the array.
    /// </summary>
    /// <returns>Returns the array capacity.</returns>
    Size getCapacity() const {
      return this->capacity;
    }
    /// <summary>
    /// Get the number of elements in the array.
    /// </summary>
    /// <returns>Returns the array length.</returns>
    Size getLength() const {
      return this->length;
    }
    /// <summary>
    /// Add the specified element at the given index by using move semantics.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">New element.</param>
    /// <returns>Returns a pointer to the corresponding element or null when wasn't possible to add it.</returns>
    ElementType* add(const Index index, ElementType&& element) {
      if (index < this->capacity) {
        using SPL::Swap;
        for (Size offset = this->length++; offset > index; offset--) {
          Swap(this->elements[offset - 1], this->elements[offset]);
        }
        Swap(this->elements[index], element);
        return &this->elements[index];
      }
      return nullptr;
    }
    /// <summary>
    /// Add a copy of the specified element at the given index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">New element.</param>
    /// <returns>Returns a pointer to the corresponding element or null when wasn't possible to add it.</returns>
    ElementType* add(const Index index, const ElementType& element) {
      ElementType copy(element);
      return this->add(index, Move(copy));
    }
    /// <summary>
    /// Merge all the given lists into a new array.
    /// </summary>
    /// <param name="pack">Pack of lists.</param>
    /// <returns>Returns the new array.</returns>
    BasicArray concat(const ListPack<T>& pack) const {
      using SPL::Swap;
      auto length = this->length;
      for (Index index = 0; index < pack.getLength(); ++index) {
        length += pack[index].getLength();
      }
      BasicArray array(length);
      for (Size offset = 0; offset < this->length; ++offset) {
        ElementType copy(this->elements[offset]);
        Swap(array.elements[array.length++], copy);
      }
      for (Index index = 0; index < pack.getLength(); ++index) {
        const auto& current = pack[index];
        for (Size offset = 0; offset < current.getLength(); ++offset) {
          ElementType copy(current.get(offset));
          Swap(array.elements[array.length++], copy);
        }
      }
      return array;
    }
    /// <summary>
    /// Get the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns a pointer to the corresponding element or null when wasn't possible to get it.</returns>
    ElementType* get(const Index index) const {
      if (index < this->length) {
        return &this->elements[index];
      }
      return nullptr;
    }
    /// <summary>
    /// Get the first index occurrence of the specified element in the array.
    /// </summary>
    /// <param name="search">Search element.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the element wasn't found.</returns>
    Index indexOf(const T& search, const Index from = 0) const {
      auto index = Math::Min(from, this->length);
      while (index < this->length) {
        if (Compare(this->elements[index], search) == 0) {
          return index;
        }
        index++;
      }
      return -1;
    }
    /// <summary>
    /// Get the last index occurrence of the specified element in the array.
    /// </summary>
    /// <param name="search">Search element.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the element wasn't found.</returns>
    Index lastIndexOf(const T& search, const Index from = -1) const {
      auto index = Math::Min(from, this->length);
      while (index > 0) {
        index--;
        if (Compare(this->elements[index], search) == 0) {
          return index;
        }
      }
      return -1;
    }
    /// <summary>
    /// Remove the first occurrence of the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns a pointer to the corresponding element or null when wasn't possible to find it.</returns>
    ElementType* remove(const Index index) {
      if (index < this->length) {
        using SPL::Swap;
        for (Size offset = index + 1; offset < this->length; offset++) {
          Swap(this->elements[offset - 1], this->elements[offset]);
        }
        return &this->elements[--this->length];
      }
      return nullptr;
    }
    /// <summary>
    /// Slice a portion of the array based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the generated array.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    BasicArray slice(const Index from, const Index to = -1) const {
      if (from > to || from > this->length - 1) {
        throw Exceptions::IndexOutOfBounds(from);
      }
      return BasicArray(&this->elements[from], Math::Min(to, this->length) - from);
    }
    /// <summary>
    /// Sort the array.
    /// </summary>
    void sort() {
      if (this->length > 1) {
        Sort(this->elements, 0, this->length - 1);
      }
    }
    /// <summary>
    /// Reverse the array (in-place).
    /// </summary>
    void reverse() {
      using SPL::Swap;
      for (Size offset = 0; offset < this->length / 2; ++offset) {
        Swap(this->elements[offset], this->elements[this->length - 1 - offset]);
      }
    }
    /// <summary>
    /// Clear the array.
    /// The current capacity will remains the same.
    /// </summary>
    void clear() {
      this->length = 0;
    }
    /// <summary>
    /// Enlarge the current capacity and move all elements.
    /// The new capacity should be greater than the current one.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    /// <returns>Returns true when the enlargement was successful, false otherwise.</returns>
    bool enlarge(const Size capacity) {
      const auto value = Math::Max(capacity, 4U);
      if (value > this->capacity) {
        this->resize(value);
        return true;
      }
      return false;
    }
    /// <summary>
    /// Shrink the current capacity and move all elements.
    /// The new capacity should be smaller than the current one and greater than the current length.
    /// </summary>
    /// <param name="capacity">New capacity.</param>
    /// <returns>Returns true when the shrinkage was successful, false otherwise.</returns>
    bool shrink(const Size capacity) {
      const auto value = Math::Max(capacity, 4U);
      if (value > this->length && value < this->capacity) {
        this->resize(value);
        return true;
      }
      return false;
    }
  public:
    /// <summary>
    /// Assign all properties from the given array.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    BasicArray& operator = (BasicArray other) noexcept {
      Swap(*this, other);
      return *this;
    }
    /// <summary>
    /// Get the array of elements.
    /// </summary>
    /// <returns>Returns the array of elements.</returns>
    operator const T* () const {
      return this->elements;
    }
  };
}
