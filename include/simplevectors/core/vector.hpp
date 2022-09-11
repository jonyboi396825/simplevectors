/**
 * basevector.hpp
 *
 * Copyright (c) 2022 Jonathan Liu. All rights reserved.
 * MIT License
 */

#ifndef INCLUDE_SVECTOR_BASEVECTOR_HPP_
#define INCLUDE_SVECTOR_BASEVECTOR_HPP_

#include <cmath>
#include <initializer_list>
#include <string>

namespace svector {
/**
 * A base vector representation
 */
template <size_t dimensions> class Vector {
public:
  /**
   * No-argument constructor
   *
   * Initializes a zero vector.
   */
  Vector() { this->m_components.fill(0); }

  /**
   * Initializes a vector given initializer list
   *
   * The initializer list should represent the components
   * of the vector in each dimension.
   *
   * @param args the initializer list
   */
  Vector(const std::initializer_list<double> args) {
    size_t counter = 0;
    for (auto num : args) {
      if (counter >= dimensions) {
        break;
      }

      this->m_components[counter] = num;
      counter++;
    }
  }

  /**
   * Copy constructor
   */
  Vector(const Vector<dimensions> &other) {
    for (size_t i = 0; i < dimensions; i++) {
      this->m_components[i] = other[i];
    }
  }

  /**
   * String form; can be used for printing
   *
   * @returns string form of vector
   */
  virtual std::string toString() const {
    std::string str = "<";
    for (size_t i = 0; i < dimensions - 1; i++) {
      str += std::to_string(this->m_components[i]);
      str += ", ";
    }

    str += std::to_string(this->m_components[dimensions - 1]);
    str += ">";

    return str;
  }

  /**
   * Adds two vectors
   */
  Vector<dimensions> operator+(const Vector<dimensions> &other) const {
    Vector<dimensions> tmp;
    for (size_t i = 0; i < dimensions; i++) {
      tmp[i] = this->m_components[i] + other[i];
    }

    return tmp;
  }

  /**
   * Subtracts two vectors
   */
  Vector<dimensions> operator-(const Vector<dimensions> &other) const {
    Vector<dimensions> tmp;
    for (size_t i = 0; i < dimensions; i++) {
      tmp[i] = this->m_components[i] - other[i];
    }

    return tmp;
  }

  /**
   * Flips direction of vector
   */
  Vector<dimensions> operator-() const {
    Vector<dimensions> tmp;
    for (size_t i = 0; i < dimensions; i++) {
      tmp[i] = -this->m_components[i];
    }

    return tmp;
  }

  /**
   * Scalar multiplication of vector
   */
  Vector<dimensions> operator*(const double other) const {
    Vector<dimensions> tmp;
    for (size_t i = 0; i < dimensions; i++) {
      tmp[i] = this->m_components[i] * other;
    }

    return tmp;
  }

  /**
   * Scalar division of vector
   */
  Vector<dimensions> operator/(const double other) const {
    Vector<dimensions> tmp;
    for (size_t i = 0; i < dimensions; i++) {
      tmp[i] = this->m_components[i] / other;
    }

    return tmp;
  }

  /**
   * Equality
   */
  bool operator==(const Vector<dimensions> &other) const {
    for (size_t i = 0; i < dimensions; i++) {
      if (this->m_components[i] == other[i]) {
        continue;
      } else {
        return false;
      }
    }

    return true;
  }

  /**
   * Inequality
   */
  bool operator!=(const Vector<dimensions> &other) const {
    return !((*this) == other);
  }

  /**
   * Adds another vector object to self
   */
  Vector<dimensions> &operator+=(const Vector<dimensions> &other) {
    for (size_t i = 0; i < dimensions; i++) {
      m_components[i] += other[i];
    }
  }

  /**
   * Subtracts another vector object from self
   */
  Vector<dimensions> &operator-=(const Vector<dimensions> &other) {
    for (size_t i = 0; i < dimensions; i++) {
      m_components[i] -= other[i];
    }
  }

  /**
   * Multiplies vector by a number
   */
  Vector<dimensions> &operator*=(const double other) {
    for (size_t i = 0; i < dimensions; i++) {
      m_components[i] *= other;
    }
  }

  /**
   * Divides vector by a number
   */
  Vector<dimensions> &operator/=(const double other) {
    for (size_t i = 0; i < dimensions; i++) {
      m_components[i] /= other;
    }
  }

  /**
   * Gets the magnitude of the vector
   *
   * @returns magnitude of vector
   */
  double magn() const {
    double sum_of_squares;
    for (auto i : m_components) {
      sum_of_squares += i * i;
    }

    return std::sqrt(sum_of_squares);
  };

  /**
   * Normalizes a vector.
   *
   * Finds the unit vector with the same direction angle as the current vector.
   *
   * @returns Normalized vector
   */
  double normalize() const { return (*this) / this->magn(); }

  /**
   * Gets a certain component of the vector given the dimension number
   *
   * @returns Dimension number
   */
  double &operator[](size_t index) const { return m_components[index]; }

  template <typename T> T componentsAs() const;

protected:
  std::array<double, dimensions> m_components;
};
} // namespace svector

#endif
