/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./array_iterator.hpp"
#include "./basic_array.hpp"

namespace SPL::Arrays {
  /// <summary>
  /// Array list class.
  /// </summary>
  /// <typeparam name="T">Element type.</typeparam>
  template<typename T>
  class ArrayList final : public List<T>, public Iterable<T> {
  private:
    /// <summary>
    /// Basic array type.
    /// </summary>
    using BasicType = BasicArray<T>;
    /// <summary>
    /// Non-constant element type.
    /// </summary>
    using ElementType = Metadata::ConstantType<T>;
    /// <summary>
    /// Basic array.
    /// </summary>
    BasicType array;
  private:
    /// <summary>
    /// Enlarge the current capacity.
    /// </summary>
    void enlarge() {
      const auto capacity = this->array.getCapacity();
      if (this->array.getLength() == capacity) {
        this->array.enlarge(capacity << 1);
      }
    }
    /// <summary>
    /// Shrink the current capacity.
    /// </summary>
    void shrink() {
      const auto capacity = this->array.getCapacity();
      if (this->array.getLength() == capacity >> 2) {
        this->array.shrink(capacity >> 1);
      }
    }
  private:
    /// <summary>
    /// Internal constructor.
    /// </summary>
    /// <param name="array">Initial array.</param>
    explicit ArrayList(BasicType& array) : ArrayList() {
      using SPL::Swap;
      Swap(this->array, array);
    }
  public:
    /// <summary>
    /// Initialized constructor for capacity.
    /// </summary>
    /// <param name="capacity">Initial capacity.</param>
    explicit ArrayList(const Size capacity) :
      array(NP2(capacity)) {}
    /// <summary>
    /// Initialized constructor for elements.
    /// </summary>
    /// <param name="elements">Initial elements.</param>
    template<Size N>
    ArrayList(const ElementType(&elements)[N]) : ArrayList(N) {
      for (const auto& element : elements) {
        this->add(element);
      }
    }
    /// <summary>
    /// Default constructor.
    /// </summary>
    ArrayList() :
      array() {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    ArrayList(const ArrayList& other) :
      array(other.array) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    ArrayList(ArrayList&& other) noexcept :
      array(Move(other.array)) {}
  public:
    /// <summary>
    /// Get the capacity of the array.
    /// </summary>
    /// <returns>Returns the array capacity.</returns>
    Size getCapacity() const {
      return this->array.getCapacity();
    }
    /// <summary>
    /// Get the number of elements in the array.
    /// </summary>
    /// <returns>Returns the array length.</returns>
    Size getLength() const override {
      return this->array.getLength();
    }
    /// <summary>
    /// Determines whether or not the array is empty.
    /// </summary>
    /// <returns>Returns true when it's empty, false otherwise.</returns>
    bool isEmpty() const override {
      return this->array.getLength() == 0;
    }
    /// <summary>
    /// Get a new array iterator.
    /// </summary>
    /// <returns>Returns the new iterator.</returns>
    UniqueIterator<T> getIterator() const override {
      auto* iterator = new ArrayIterator<T>(this->array);
      return UniqueIterator<T>(iterator);
    }
    /// <summary>
    /// Add the specified element at the end of the array by using move semantics.
    /// When the array is at its capacity, the current capacity will double.
    /// </summary>
    /// <param name="element">New element.</param>
    /// <returns>Returns the current length of the array.</returns>
    Size add(ElementType&& element) override {
      this->enlarge();
      this->array.add(this->array.getLength(), Forward<ElementType>(element));
      return this->array.getLength();
    }
    /// <summary>
    /// Add a copy of the specified element at the end of the array.
    /// When the array is at its capacity, the current capacity will double.
    /// </summary>
    /// <param name="element">New element.</param>
    /// <returns>Returns the current length of the array.</returns>
    Size add(const ElementType& element) override {
      ElementType copy(element);
      return this->add(Move(copy));
    }
    /// <summary>
    /// Add the specified element at the specified index by using move semantics.
    /// When the array is at its capacity, the current capacity will double.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">New element.</param>
    /// <returns>Returns the current length of the array.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    Size add(const Index index, ElementType&& element) override {
      if (index > this->array.getLength()) {
        throw Exceptions::IndexOutOfBounds(index);
      }
      this->enlarge();
      this->array.add(index, Forward<ElementType>(element));
      return this->array.getLength();
    }
    /// <summary>
    /// Add a copy of the specified element at the specified index.
    /// When the array is at its capacity, the current capacity will double.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">New element.</param>
    /// <returns>Returns the current length of the array.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    Size add(const Index index, const ElementType& element) override {
      ElementType copy(element);
      return this->add(index, Move(copy));
    }
    /// <summary>
    /// Replace the element at the specified index with the given one by using move semantics.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">New element.</param>
    /// <returns>Returns the replaced element.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    T set(const Index index, ElementType&& element) override {
      auto* current = this->array.get(index);
      if (current == nullptr) {
        throw Exceptions::IndexOutOfBounds(index);
      }
      using SPL::Swap;
      T previous(Move(*current));
      Swap(*current, element);
      return previous;
    }
    /// <summary>
    /// Replace the element at the specified index with a copy of the given one.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">Element.</param>
    /// <returns>Returns the replaced element.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    T set(const Index index, const ElementType& element) override {
      ElementType copy(element);
      return this->set(index, Move(copy));
    }
    /// <summary>
    /// Merge all the given list into a new array.
    /// </summary>
    /// <param name="pack">Pack of lists.</param>
    /// <returns>Returns the new array.</returns>
    UniqueList<T> concat(const ListPack<T>& pack) const override {
      auto array = this->array.concat(pack);
      return UniqueList<T>(new ArrayList(array));
    }
    /// <summary>
    /// Get the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding element.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    T& get(const Index index) const override {
      auto* current = this->array.get(index);
      if (current == nullptr) {
        throw Exceptions::IndexOutOfBounds(index);
      }
      return *current;
    }
    /// <summary>
    /// Get a copy of the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">Output element.</param>
    /// <returns>Returns true when the element was found, false otherwise.</returns>
    bool get(const Index index, ElementType& element) const override {
      auto* current = this->array.get(index);
      if (current != nullptr) {
        element = *current;
        return true;
      }
      return false;
    }
    /// <summary>
    /// Get the first index occurrence of the specified element in the array.
    /// </summary>
    /// <param name="search">Search element.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the element wasn't found.</returns>
    Index indexOf(const T& search, const Index from = 0) const override {
      return this->array.indexOf(search, from);
    }
    /// <summary>
    /// Get the last index occurrence of the specified element in the array.
    /// </summary>
    /// <param name="search">Search element.</param>
    /// <param name="from">From the zero-based index.</param>
    /// <returns>Returns the corresponding index or -1 when the element wasn't found.</returns>
    Index lastIndexOf(const T& search, const Index from = -1) const override {
      return this->array.lastIndexOf(search, from);
    }
    /// <summary>
    /// Determines whether or not the array contains the specified element.
    /// </summary>
    /// <param name="search">Search element.</param>
    /// <returns>Returns true when the element was found, false otherwise.</returns>
    bool contains(const T& search) const override {
      return this->array.indexOf(search) != -1;
    }
    /// <summary>
    /// Remove the element that corresponds to the specified index from the array.
    /// When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the removed element.</returns>
    /// <exception cref="SPL::Exceptions::IndexOutOfBounds">Throws when the specified index is out of bounds.</exception>
    T remove(const Index index) override {
      auto* current = this->array.remove(index);
      if (current == nullptr) {
        throw Exceptions::IndexOutOfBounds(index);
      }
      T element(Move(*current));
      this->shrink();
      return element;
    }
    /// <summary>
    /// Remove the element that corresponds to the specified index from the array.
    /// When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <param name="element">Output element.</param>
    /// <returns>Returns true when the element was removed, false otherwise.</returns>
    bool remove(const Index index, ElementType& element) override {
      auto* current = this->array.remove(index);
      if (current != nullptr) {
        using SPL::Swap;
        element = ElementType();
        Swap(element, *current);
        this->shrink();
        return true;
      }
      return false;
    }
    /// <summary>
    /// Remove the first occurrence of the specified element from the array.
    /// When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.
    /// </summary>
    /// <param name="element">Element reference.</param>
    /// <returns>Returns true when the element was removed, false otherwise.</returns>
    bool remove(ElementType& element) override {
      auto index = this->array.indexOf(element);
      if (index != -1) {
        this->array.remove(index);
        this->shrink();
        return true;
      }
      return false;
    }
    /// <summary>
    /// Slice a portion of the array based on the given range and generate a new one.
    /// </summary>
    /// <param name="from">From the zero-based index.</param>
    /// <param name="to">To the zero-based index.</param>
    /// <returns>Returns the generated array.</returns>
    /// <exception cref="SPL::IndexOutOfBoundsException">Throws when the specified index is out of bounds.</exception>
    UniqueList<T> slice(const Index from, const Index to = -1) const override {
      auto array = this->array.slice(from, to);
      return UniqueList<T>(new ArrayList(array));
    }
    /// <summary>
    /// Sort the array.
    /// </summary>
    void sort() override {
      this->array.sort();
    }
    /// <summary>
    /// Reverse the array (in-place).
    /// </summary>
    void reverse() override {
      this->array.reverse();
    }
    /// <summary>
    /// Clear the array.
    /// </summary>
    void clear() override {
      this->array.clear();
    }
  public:
    /// <summary>
    /// Get the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero based index.</param>
    /// <returns>Returns the corresponding element.</returns>
    const T& operator [](const Index index) const override {
      return this->get(index);
    }
    /// <summary>
    /// Get the element that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding element.</returns>
    T& operator [](const Index index) override {
      return this->get(index);
    }
    /// <summary>
    /// Assign all properties from the given array.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    ArrayList& operator = (ArrayList other) noexcept {
      this->array = Move(other.array);
      return *this;
    }
  };
}
