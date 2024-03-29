/**
 * @file vector.hpp
 *
 * @brief Contains a base vector representation.
 *
 * @copyright Copyright (c) 2023 Jonathan Liu. This project is released under
 * the MIT License. All rights reserved.
 */

#ifndef INCLUDE_SVECTOR_BASEVECTOR_HPP_
#define INCLUDE_SVECTOR_BASEVECTOR_HPP_

#include <algorithm>        // std::min
#include <array>            // std::array
#include <cmath>            // std::atan2, std::sqrt
#include <cstddef>          // std::size_t
#include <cstdint>          // std::int8_t
#include <initializer_list> // std::initializer_list
#include <string>           // std::string, std::to_string
#include <type_traits>      // std::is_arithmetic

namespace svector {
// COMBINER_PY_START
/**
 * @brief A base vector representation.
 *
 * @note The binary +, -, *, /, ==, and != operators are by default implemented
 * in functions.hpp. To use the class implementation rather than the one in
 * functions.hpp, define the variable SVECTOR_USE_CLASS_OPERATORS.
 *
 * @tparam D The number of dimensions.
 * @tparam T Vector type.
 */
template <std::size_t D, typename T = double> class Vector {
public:
  // makes sure that type is numeric
  static_assert(std::is_arithmetic<T>::value, "Vector type must be numeric");

#ifdef SVECTOR_EXPERIMENTAL_COMPARE
  template <std::size_t D1, std::size_t D2, typename T1, typename T2>
  friend bool operator<(const Vector<D1, T1> &, const Vector<D2, T2> &);

  template <std::size_t D1, std::size_t D2, typename T1, typename T2>
  friend bool operator<=(const Vector<D1, T1> &, const Vector<D2, T2> &);

  template <std::size_t D1, std::size_t D2, typename T1, typename T2>
  friend bool operator>(const Vector<D1, T1> &, const Vector<D2, T2> &);

  template <std::size_t D1, std::size_t D2, typename T1, typename T2>
  friend bool operator>=(const Vector<D1, T1> &, const Vector<D2, T2> &);
#endif

  typedef
      typename std::array<T, D>::iterator iterator; //!< An std::array::iterator
  typedef typename std::array<T, D>::const_iterator
      const_iterator; //!< An std::array::const_iterator
  typedef typename std::array<T, D>::reverse_iterator
      reverse_iterator; //!< An std::array::reverse_iterator
  typedef typename std::array<T, D>::const_reverse_iterator
      const_reverse_iterator; //!< An std::array::const_reverse_iterator

  /**
   * @brief No-argument constructor
   *
   * Initializes a zero vector (all components are 0).
   */
  Vector() { this->m_components.fill(0); }

  /**
   * @brief Initializes a vector given initializer list
   *
   * The initializer list should represent the components of the vector in each
   * dimension. If the size of the initializer list is greater than the number
   * of dimensions given, then the vector only initializes with the first D
   * elements in the list, where D is the number of dimensions. If the size of
   * the initializer list is less than the number of dimensions given, then the
   * vector fills the rest of the dimensions with the value 0.
   *
   * @param args the initializer list.
   */
  Vector(const std::initializer_list<T> args) {
    // in case length of args < dimensions
    this->m_components.fill(0);

    std::size_t counter = 0;
    for (const auto &num : args) {
      if (counter >= D) {
        break;
      }

      this->m_components[counter] = num;
      counter++;
    }
  }

  /**
   * @brief Copy constructor
   *
   * Copies from another vector to an uninitialized vector.
   */
  Vector(const Vector<D, T> &other) {
    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] = other[i];
    }
  }

  /**
   * @brief Move constructor
   *
   * Uses C++ default move constructor.
   */
  Vector(Vector<D, T> &&) noexcept = default;

  /**
   * @brief Assignment operator
   *
   * Copies from another vector to a vector whose values already exist.
   */
  Vector<D, T> &operator=(const Vector<D, T> &other) {
    // check if assigning to self
    if (this == &other) {
      return *this;
    }

    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] = other[i];
    }

    return *this;
  }

  /**
   * @brief Move assignment operator
   *
   * Uses C++ default move assignment operator.
   */
  Vector<D, T> &operator=(Vector<D, T> &&) noexcept = default;

  /**
   * @brief Destructor
   *
   * Uses C++ default destructor.
   */
  virtual ~Vector() = default;

  /**
   * @brief Returns string form of vector
   *
   * This string form can be used for printing.
   *
   * @returns The string form of the vector.
   */
  virtual std::string toString() const {
    std::string str = "<";
    for (std::size_t i = 0; i < D - 1; i++) {
      str += std::to_string(this->m_components[i]);
      str += ", ";
    }

    str += std::to_string(this->m_components[D - 1]);
    str += ">";

    return str;
  }

#ifdef SVECTOR_USE_CLASS_OPERATORS
  /**
   * @brief Vector addition
   *
   * Performs vector addition and returns a new vector representing the sum of
   * the two vectors.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @note The dimensions of the other vector must be the same
   * as the current one.
   *
   * @param other The other vector.
   *
   * @returns A new vector representing the vector sum.
   */
  Vector<D, T> operator+(const Vector<D, T> &other) const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = this->m_components[i] + other[i];
    }

    return tmp;
  }

  /**
   * @brief Vector subtraction
   *
   * Performs vector subtraction and returns a new vector representing the
   * difference of the two vectors.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @note The dimensions of the other vector must be the same
   * as the current one.
   *
   * @param other The other vector.
   *
   * @returns A new vector representing the vector difference.
   */
  Vector<D, T> operator-(const Vector<D, T> &other) const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = this->m_components[i] - other[i];
    }

    return tmp;
  }

  /**
   * @brief Scalar multiplication
   *
   * Performs scalar multiplication and returns a new vector representing the
   * product.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @param other The other vector.
   *
   * @returns A new vector representing the scalar product.
   */
  Vector<D, T> operator*(const T other) const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = this->m_components[i] * other;
    }

    return tmp;
  }

  /**
   * @brief Scalar division
   *
   * Performs scalar division and returns a new vector representing the
   * quotient.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @param other The other vector.
   *
   * @returns A new vector representing the scalar quotient.
   */
  Vector<D, T> operator/(const T other) const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = this->m_components[i] / other;
    }

    return tmp;
  }

  /**
   * @brief Compares equality of two vectors.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @note The dimensions of the other vector must be the same
   * as the current one.
   *
   * @param other The other vector.
   *
   * @returns A boolean representing whether the vectors compare equal.
   */
  bool operator==(const Vector<D, T> &other) const {
    for (std::size_t i = 0; i < D; i++) {
      if (this->m_components[i] != other[i]) {
        return false;
      }
    }

    return true;
  }

  /**
   * @brief Compares inequality of two vectors.
   *
   * @note This method is only used if SVECTOR_USE_CLASS_OPERATORS is
   * defined. Otherwise, the binary operators in functions.hpp are used.
   *
   * @note The dimensions of the other vector must be the same
   * as the current one.
   *
   * @param other The other vector.
   *
   * @returns A boolean representing whether the vectors do not compare equal.
   */
  bool operator!=(const Vector<D, T> &other) const {
    return !((*this) == other);
  }
#endif

  /**
   * @brief Negative of a vector
   *
   * Makes all components of the vector negative of what they currently are.
   *
   * This can also be thought of flipping the direction of the vector.
   *
   * @returns A new vector representing the negative of the current vector.
   */
  Vector<D, T> operator-() const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = -this->m_components[i];
    }

    return tmp;
  }

  /**
   * @brief Positive of a vector
   *
   * Creates new vector where the unary plus operator is applied to each
   * component. In almost all cases, this returns the original vector.
   *
   * @returns The current vector.
   */
  Vector<D, T> operator+() const {
    Vector<D, T> tmp;
    for (std::size_t i = 0; i < D; i++) {
      tmp[i] = +this->m_components[i];
    }

    return tmp;
  }

  /**
   * @brief In-place addition
   *
   * Adds another vector object to the current object.
   *
   * @param other The other vector to add.
   */
  Vector<D, T> &operator+=(const Vector<D, T> &other) {
    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] += other[i];
    }

    return *this;
  }

  /**
   * @brief In-place subtraction
   *
   * Subtracts another vector object from the current object.
   *
   * @param other The other vector to subtract.
   */
  Vector<D, T> &operator-=(const Vector<D, T> &other) {
    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] -= other[i];
    }

    return *this;
  }

  /**
   * @brief In-place scalar multiplication
   *
   * Performs scalar multiplication on the current object.
   *
   * @param other The number to multiply by.
   */
  Vector<D, T> &operator*=(const T other) {
    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] *= other;
    }

    return *this;
  }

  /**
   * @brief In-place scalar division
   *
   * Performs scalar division on the current object.
   *
   * @param other The number to divide by.
   */
  Vector<D, T> &operator/=(const T other) {
    for (std::size_t i = 0; i < D; i++) {
      this->m_components[i] /= other;
    }

    return *this;
  }

  /**
   * @brief Dot product
   *
   * Calculates the dot product of two vectors.
   *
   * @note The dimensions of the other vector must be the same
   * as the current one.
   *
   * @param other The other vector to dot the current vector with.
   *
   * @returns A new vector representing the dot product of the two vectors.
   */
  T dot(const Vector<D, T> &other) const {
    T result = 0;

    for (std::size_t i = 0; i < D; i++) {
      result += this->m_components[i] * other[i];
    }

    return result;
  }

  /**
   * @brief Magnitude
   *
   * Gets the magnitude of the vector.
   *
   * @returns The magnitude of the vector.
   */
  T magn() const {
    T sum_of_squares = 0;

    for (const auto &i : this->m_components) {
      sum_of_squares += i * i;
    }

    return std::sqrt(sum_of_squares);
  };

  /**
   * @brief Normalizes a vector.
   *
   * Finds the unit vector with the same direction angle as the current vector.
   *
   * @note This method will result in undefined behavior if the vector is a zero
   * vector (if the magnitude equals zero).
   *
   * @returns A new vector representing the normalized vector.
   */
  Vector<D, T> normalize() const { return (*this) / this->magn(); }

  /**
   * @brief Gets the number of dimensions.
   *
   * @returns Number of dimensions.
   */
  constexpr std::size_t numDimensions() const { return D; }

  /**
   * @brief Determines whether the current vector is a zero vector.
   *
   * @returns Whether the current vector is a zero vector.
   */
  bool isZero() const { return this->magn() == 0; }

  /**
   * @brief Value of a certain component of a vector
   *
   * Gets a reference to a specific component of the vector given the dimension
   * number.
   *
   * @param index The dimension number.
   *
   * @returns A constant reference to that dimension's component of the vector.
   */
  const T &operator[](const std::size_t index) const {
    return this->m_components[index];
  }

  /**
   * @brief Sets value of a certain component
   *
   * Sets a certain component of the vector given the dimension number.
   *
   * @param index The dimension number.
   */
  T &operator[](const std::size_t index) { return this->m_components[index]; }

  /**
   * @brief Value of a certain component of a vector
   *
   * Gets a reference to a specific component of the vector given the dimension
   * number.
   *
   * Throws an out_of_range exception if the given number is out of bounds.
   *
   * @param index The dimension number.
   *
   * @returns A constant reference to that dimension's component of the vector.
   */
  const T &at(const std::size_t index) const {
    return this->m_components.at(index);
  }

  /**
   * @brief Sets value of a certain component
   *
   * Sets a certain component of the vector given the dimension number.
   *
   * Throws an out_of_range exception if the given number is out of bounds.
   *
   * @param index The dimension number.
   */
  T &at(const std::size_t index) { return this->m_components.at(index); }

  /**
   * @brief Iterator of first element
   *
   * Returns an iterator to the first dimension of the vector. This iterator
   * will be equal to end() for a zero-dimension vector.
   *
   * This can be used for looping through the dimensions of a vector.
   *
   * @returns An iterator to the first dimension of the vector.
   */
  iterator begin() noexcept { return iterator{this->m_components.begin()}; }

  /**
   * @brief Const interator of first element
   *
   * Returns a constant iterator to the first dimension of the vector. This
   * iterator will be equal to end() for a zero-dimension vector.
   *
   * @returns A constant iterator to the first dimension of the vector.
   */
  const_iterator begin() const noexcept {
    return const_iterator{this->m_components.begin()};
  }

  /**
   * @brief Interator of last element + 1
   *
   * Returns an iterator to the element following the last dimension of the
   * vector.
   *
   * This iterator is a placeholder and attempting to access it will result in
   * undefined behavior.
   *
   * This can be used for looping through the dimensions of a vector.
   *
   * @returns An iterator to the element following the last dimension.
   */
  iterator end() noexcept { return iterator{this->m_components.end()}; }

  /**
   * @brief Const interator of last element + 1
   *
   * Returns a constant iterator to the element following the last dimension of
   * the vector.
   *
   * This iterator is a placeholder and attempting to access it will result in
   * undefined behavior.
   *
   * @returns A constant iterator to the element following the last dimension.
   */
  const_iterator end() const noexcept {
    return const_iterator{this->m_components.end()};
  }

  /**
   * @brief Reverse iterator to last element
   *
   * Returns a reverse iterator to the first dimension of the reversed vector.
   * It corresponds to the last dimension of the original vector. The iterator
   * will be equal to rend() for a zero-dimension vector.
   *
   * This can be used for looping through the dimensions of a vector.
   *
   * @returns A reverse iterator to the first dimension.
   */
  reverse_iterator rbegin() noexcept {
    return reverse_iterator{this->m_components.rbegin()};
  }

  /**
   * @brief Const reverse iterator to last element
   *
   * Returns a constant reverse iterator to the first dimension of the reversed
   * vector. It corresponds to the last dimension of the original vector. The
   * iterator will be equal to rend() for a zero-dimension vector.
   *
   * @returns A constant reverse iterator to the first dimension.
   */
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator{this->m_components.rbegin()};
  }

  /**
   * @brief Reverse iterator to first element - 1
   *
   * Returns a reverse iterator to the element following the last dimension of
   * the reversed vector. It corresponds to the element preceding the first
   * dimension of the original vector.
   *
   * This iterator is a placeholder and attempting to access it will result in
   * undefined behavior.
   *
   * This can be used for looping through the dimensions of a vector.
   *
   * @returns A reverse iterator to the element following the last dimension.
   */
  reverse_iterator rend() noexcept {
    return reverse_iterator{this->m_components.rend()};
  }

  /**
   * @brief Const reverse iterator to first element - 1
   *
   * Returns a constant reverse iterator to the element following the last
   * dimension of the reversed vector. It corresponds to the element preceding
   * the first dimension of the original vector.
   *
   * This iterator is a placeholder and attempting to access it will result in
   * undefined behavior.
   *
   * @returns A constant reverse iterator to the element following the last
   * dimension.
   */
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator{this->m_components.rend()};
  }

protected:
  std::array<T, D> m_components; //!< An array of components for the vector.

#ifdef SVECTOR_EXPERIMENTAL_COMPARE
private:
  /**
   * @brief Compares elements between vectors lexographically (EXPERIMENTAL).
   *
   * Loops through components one by one from left to right, and at any
   * component, if the component of this vector is less than the component of
   * the other vector, then returns -1. If the component of this vector is
   * greater than the component of the other vector, then returns 1. If all
   * components are equal, the returns 0.
   *
   * If this vector has fewer components, then returns -1, and if other vector
   * has fewer components, returns 1.
   *
   * @tparam D2 The number of dimensions of the other vector.
   * @tparam T2 Vector type of the other vector.
   *
   * @param other The other vector to compare to.
   *
   * @returns -1 if the current vector compares less, 0 if the current vector
   * compares equal, and 1 if the current vector compares greater.
   */
  template <std::size_t D2, typename T2>
  std::int8_t compare(const Vector<D2, T2> &other) const noexcept {
    std::size_t min_dim = std::min(D, D2);
    std::size_t counter = 0;

// to suppress MSVC warning
#ifdef _MSC_VER
    if constexpr (D != D2) {
#else
    if (D != D2) {
#endif
      // check dimensions first
      return D < D2 ? -1 : 1;
    }

    // compare one by one
    for (std::size_t i = 0; i < min_dim; i++) {
      if (this->m_components[i] == other[i]) {
        counter++;
      } else if (this->m_components[i] < other[i]) {
        return -1;
      } else {
        return 1;
      }
    }

    if (counter != D || counter != D2) {
      return -1;
    }

    // means two vectors are equal
    return 0;
  }
#endif
};
// COMBINER_PY_END
} // namespace svector

#endif
