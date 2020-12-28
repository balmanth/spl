/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "core.hpp"
#include "interfaces.hpp"

namespace SPL::Tests {
  /// <summary>
  /// Mock class.
  /// </summary>
  class Mock : public Comparable<Mock> {
  private:
    /// <summary>
    /// Instances counter.
    /// It's used for testing constructors and destructors.
    /// </summary>
    Size* instances;
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Mock& source, Mock& target) noexcept {
      using SPL::Swap;
      Swap(source.instances, target.instances);
    }
    /// <summary>
    /// Internal constructor.
    /// </summary>
    /// <param name="instances">Pointer to the instance counter.</param>
    explicit Mock(Size* const instances) : instances(instances) {
      if (this->instances != nullptr) {
        (*this->instances)++;
      }
    }
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="counter">Counter reference.</param>
    explicit Mock(Size& counter) :
      Mock(&counter) {}
    /// <summary>
    /// Default constructor.
    /// </summary>
    Mock() :
      instances(nullptr) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Mock(const Mock& other) :
      Mock(other.instances) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Mock(Mock&& other) noexcept : Mock() {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Mock() {
      if (this->instances != nullptr) {
        (*this->instances)--;
      }
    }
  public:
    /// <summary>
    /// Compare both objects.
    /// </summary>
    /// <param name="other">Other object.</param>
    /// <returns>
    /// Returns -1 when this object is less than the other one.
    /// Returns  0 when this object is equals to the other one.
    /// Returns  1 when this object is greater than the other one.
    /// </returns>
    int compare(const Mock& other) const override {
      return SPL::Compare(this, &other);
    }
  public:
    /// <summary>
    /// Assign all properties from the given mock.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Mock& operator = (Mock other) {
      Swap(*this, other);
      return *this;
    }
  };
}

namespace SPL::HashTables {
  /// <summary>
  /// Mock hash function.
  /// </summary>
  /// <typeparam name="T">Key type.</typeparam>
  /// <param name="key">Entry key.</param>
  /// <returns>Returns the hash code.</returns>
  inline Id Function(const SPL::Tests::Mock& key) {
    return reinterpret_cast<Id>(&key);
  }
}
