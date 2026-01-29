#pragma once

#include <cmath>
#include <concepts>
#include <iostream>
#include <random>
#include <stdexcept>

#include "types.h"

template <numeric T>
class Vec2 {
 public:
  Vec2() = default;
  Vec2(T p1, T p2) : m_x{p1}, m_y{p2} {}

  static Vec2<T> create_unit_vec() { return Vec2<T>(T{1}, T{1}); }

  T x() const { return m_x; }
  T y() const { return m_y; }

  void x(T num) { m_x = num; }
  void y(T num) { m_y = num; }
  void set(T num) { m_x = m_y = num; }
  void set(T num1, T num2) {
    m_x = num1;
    m_y = num2;
  }

  T operator[](int i) const {
    if (i < 0 || i > 1) throw std::out_of_range("Index out of range");
    return i == 0 ? m_x : m_y;
  }

  T& operator[](int i) {
    if (i < 0 || i > 1) throw std::out_of_range("Index out of range");
    return i == 0 ? m_x : m_y;
  }

  auto operator<=>(const Vec2<T>&) const = default;

  Vec2<T> operator+() const { return Vec2<T>(m_x, m_y); };
  Vec2<T> operator-() const { return Vec2<T>(-m_x, -m_y); }

  void normalize() {
    auto l = length();
    if (l < std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error("Cannot normalize zero-length 2D vector");
    }
    m_x = static_cast<T>(m_x / l);
    m_y = static_cast<T>(m_y / l);
  }

  auto length() const { return static_cast<T>(sqrt(m_x * m_x + m_y * m_y)); }
  bool is_zero() const { return *this == Vec2<T>(T{0}, T{0}); }

 private:
  T m_x = T{0};
  T m_y = T{0};
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
inline std::istream& operator>>(std::istream& in, Vec2<T>& v) {
  T x, y;
  in >> x >> y;
  v.set(x, y);
  return in;
}

template <numeric T>
inline std::ostream& operator<<(std::ostream& out, const Vec2<T>& v) {
  out << "(" << v.x() << "," << v.y() << ")";
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
Vec2<T> operator+(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x() + v2.x(), v1.y() + v2.y());
}

template <numeric T>
Vec2<T> operator+(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x() + num, v.y() + num);
}

template <numeric T>
Vec2<T> operator+(T num, const Vec2<T>& v) {
  return v + num;
}

template <numeric T>
Vec2<T> operator-(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x() - v2.x(), v1.y() - v2.y());
}

template <numeric T>
Vec2<T> operator-(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x() - num, v.y() - num);
}

template <numeric T>
Vec2<T> operator-(T num, const Vec2<T>& v) {
  return v - num;
}

template <numeric T>
Vec2<T> operator*(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x() * v2.x(), v1.y() * v2.y());
}

template <numeric T>
Vec2<T> operator*(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x() * num, v.y() * num);
}

template <numeric T>
Vec2<T> operator*(T num, const Vec2<T>& v) {
  return v * num;
}

template <numeric T>
Vec2<T> operator/(const Vec2<T>& v1, const Vec2<T>& v2) {
  if (v2.is_zero()) {
    throw std::runtime_error("Cannot divide by zero 2D vector");
  }
  return Vec2<T>(v1.x() / v2.x(), v1.y() / v2.y());
}

template <numeric T>
Vec2<T> operator/(const Vec2<T>& v, T num) {
  if (num == T{0}) {
    throw std::runtime_error("Cannot divide by zero number");
  }
  return Vec2<T>(v.x() / num, v.y() / num);
}

//--------------------------------------------
// Other vector operations
//--------------------------------------------

template <numeric T>
T dot(const Vec2<T>& v1, const Vec2<T>& v2) {
  auto v = v1 * v2;
  return v.x() + v.y();
}

template <numeric T>
Vec2<T> normalized(const Vec2<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error("Cannot normalize zero-length 2D vector");
  }
  return Vec2<T>{static_cast<T>(v.x() / l), static_cast<T>(v.y() / l)};
}
