/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types/pick.hpp"
#include "./move.hpp"
#include "./types.hpp"

namespace SPL {
  /// <summary>
  /// Tuple class.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="...N">Next values.</typeparam>
  template<typename T, typename ...N>
  class Tuple {
  private:
    /// <summary>
    /// Tuple value class.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <typeparam name="V">Value type.</typeparam>
    template<Size I, typename V>
    class Value {
    private:
      /// <summary>
      /// Exchange all properties from the given objects.
      /// </summary>
      /// <param name="source">Source object.</param>
      /// <param name="target">Target object.</param>
      friend void Swap(Value<I, V>& source, Value<I, V>& target) noexcept {
        using SPL::Swap;
        Swap(source.value, target.value);
      }
    public:
      /// <summary>
      /// Tuple value.
      /// </summary>
      V value;
      /// <summary>
      /// Initialized constructor.
      /// </summary>
      /// <param name="value">Initial value.</param>
      explicit Value(const V& value) :
        value(value) {}
      /// <summary>
      /// Default constructor.
      /// </summary>
      Value() :
        value() {}
      /// <summary>
      /// Copy constructor.
      /// </summary>
      /// <param name="value">Other instance.</param>
      Value(const Value<I, V>& other) :
        value(other.value) {}
      /// <summary>
      /// Move constructor.
      /// </summary>
      /// <param name="value">Other instance.</param>
      Value(Value<I, V>&& other) noexcept : Value() {
        Swap(*this, other);
      }
    public:
      /// <summary>
      /// Assign all properties from the given value.
      /// </summary>
      /// <param name="other">Other instance.</param>
      /// <returns>Returns the instance itself.</returns>
      Value<I, V>& operator = (Value<I, V> other) noexcept {
        Swap(*this, other);
        return *this;
      }
    };
  public:
    /// <summary>
    /// Tuple element declaration.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <typeparam name="...V">Value types.</typeparam>
    template<Index I, typename ...V>
    class Element;
    /// <summary>
    /// Tuple element class.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <typeparam name="V">Value type.</typeparam>
    template<Index I, typename V>
    class Element<I, V> : public Value<I, V> {
    private:
      /// <summary>
      /// Exchange all properties from the given objects.
      /// </summary>
      /// <param name="source">Source object.</param>
      /// <param name="target">Target object.</param>
      friend void Swap(Element<I, V>& source, Element<I, V>& target) noexcept {
        using SPL::Swap;
        Swap<Value<I, V>>(source, target);
      }
    public:
      /// <summary>
      /// Initialized constructor.
      /// </summary>
      /// <param name="value">Initial value.</param>
      explicit Element(const V& value) :
        Value<I, V>(value) {}
      /// <summary>
      /// Default constructor.
      /// </summary>
      Element() :
        Value<I, V>() {}
      /// <summary>
      /// Copy constructor.
      /// </summary>
      /// <param name="other">Other instance.</param>
      Element(const Element<I, V>& other) :
        Value<I, V>(other) {}
      /// <summary>
      /// Move constructor.
      /// </summary>
      /// <param name="other">Other instance.</param>
      Element(Element<I, V>&& other) noexcept : Element() {
        Swap(*this, other);
      }
    public:
      /// <summary>
      /// Assign all properties from the given element.
      /// </summary>
      /// <param name="other">Other instance.</param>
      /// <returns>Returns the instance itself.</returns>
      Element<I, V>& operator = (Element<I, V> other) noexcept {
        using SPL::Swap;
        Swap(*this, other);
        return *this;
      }
    };
    /// <summary>
    /// Tuple element class.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <typeparam name="V">Value type.</typeparam>
    /// <typeparam name="...R">Remaining types.</typeparam>
    template<Index I, typename V, typename ...R>
    class Element<I, V, R...> : public Value<I, V>, public Element<I + 1, R...> {
    private:
      /// <summary>
      /// Exchange all properties from the given objects.
      /// </summary>
      /// <param name="source">Source object.</param>
      /// <param name="target">Target object.</param>
      friend void Swap(Element<I, V, R...>& source, Element<I, V, R...>& target) noexcept {
        using SPL::Swap;
        Swap<Value<I, V>>(source, target);
        Swap<Element<I + 1, R...>>(source, target);
      }
    public:
      /// <summary>
      /// Initialized constructor.
      /// </summary>
      /// <param name="value">Initial value.</param>
      Element(const V& value, const R& ...values) :
        Value<I, V>(value), Element<I + 1, R...>(values...) {}
      /// <summary>
      /// Default constructor.
      /// </summary>
      Element() :
        Value<I, V>(), Element<I + 1, R...>() {}
      /// <summary>
      /// Copy constructor.
      /// </summary>
      /// <param name="other">Other instance.</param>
      Element(const Element<I, V, R...>& other) :
        Value<I, V>(other), Element<I + 1, R...>(other) {}
      /// <summary>
      /// Move constructor.
      /// </summary>
      /// <param name="other">Other instance.</param>
      Element(Element<I, V, N...>&& other) noexcept : Element() {
        Swap(*this, other);
      }
      /// <summary>
      /// Assign all properties from the given element.
      /// </summary>
      /// <param name="other">Other instance.</param>
      /// <returns>Returns the instance itself.</returns>
      Element<I, V, N...>& operator = (Element<I, V, N...> other) noexcept {
        Swap(*this, other);
        return *this;
      }
    };
  private:
    /// <summary>
    /// Tuple elements.
    /// </summary>
    Element<0, T, N...> elements;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Tuple<T, N...>& source, Tuple<T, N...>& target) noexcept {
      using SPL::Swap;
      Swap(source.elements, target.elements);
    }
  public:
    /// <summary>
    /// Tuple types.
    /// </summary>
    template<Index I>
    using Type = typename Types::Pick<I, T, N...>::Type;
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="value">Initial value.</param>
    /// <param name="...values">Initial values.</param>
    Tuple(const T& value, const N&... values) :
      elements(value, values...) {};
    /// <summary>
    /// Default constructor.
    /// </summary>
    Tuple() :
      elements() {};
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Tuple(const Tuple<T, N...>& other) :
      elements(other.elements) {};
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Tuple(Tuple<T, N...>&& other) noexcept : Tuple() {
      Swap(*this, other);
    }
    /// <summary>
    /// Get the tuple length.
    /// </summary>
    /// <returns>Returns the tuple length.</returns>
    Size getLength() const {
      return sizeof...(N) + 1;
    }
    /// <summary>
    /// Get the tuple value that corresponds to the given index.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <returns>Returns the value.</returns>
    template<Index I>
    Type<I>& get() const {
      return static_cast<Value<I, Type<I>>&>(this->elements).value;
    }
    /// <summary>
    /// Get the tuple value that corresponds to the given index.
    /// </summary>
    /// <typeparam name="I">Value index.</typeparam>
    /// <returns>Returns the value.</returns>
    template<Index I>
    Type<I>& get() {
      return static_cast<Value<I, Type<I>>&>(this->elements).value;
    }
    /// <summary>
    /// Set the tuple value that corresponds to the given index.
    /// </summary>
    /// <param name="value">Tuple value.</param>
    /// <returns>Returns the previous tuple value.</returns>
    template<Index I>
    Type<I> set(const Type<I>& value) {
      Type<I>& current = this->get<I>();
      Type<I> previous(Move(current));
      current = value;
      return previous;
    }
  public:
    /// <summary>
    /// Assign all properties from the given tuple.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Tuple<T, N...>& operator = (Tuple<T, N...> other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
  /// <summary>
  /// Tuple constructor deduction.
  /// </summary>
  /// <typeparam name="T">Value type.</typeparam>
  /// <typeparam name="...N">Next values.</typeparam>
  template<typename T, typename ...N>
  Tuple(T, N...)->Tuple<T, N...>;
}
