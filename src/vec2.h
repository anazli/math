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
  constexpr Vec2() = default;
  constexpr Vec2(T p1, T p2) : x{p1}, y{p2} {}

  static constexpr Vec2<T> create_unit_vec() { return Vec2<T>(T{1}, T{1}); }

  constexpr auto operator<=>(const Vec2<T>&) const = default;

  constexpr Vec2<T> operator+() const { return Vec2<T>(x, y); };
  constexpr Vec2<T> operator-() const { return Vec2<T>(-x, -y); }

  constexpr void normalize() {
    auto l = length();
    if (l < std::numeric_limits<double>::epsilon()) {
      l += static_cast<T>(1E-6);
    }
    x = static_cast<T>(x / l);
    y = static_cast<T>(y / l);
  }

  constexpr auto length() const { return static_cast<T>(sqrt(x * x + y * y)); }
  constexpr bool is_zero() const { return *this == Vec2<T>(T{0}, T{0}); }

 public:
  T x = T{0};
  T y = T{0};
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
  v.x = x;
  v.y = y;
  return in;
}

template <numeric T>
inline std::ostream& operator<<(std::ostream& out, const Vec2<T>& v) {
  out << "(" << v.x << "," << v.y << ")";
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
constexpr Vec2<T> operator+(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <numeric T>
constexpr Vec2<T> operator+(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x + num, v.y + num);
}

template <numeric T>
constexpr Vec2<T> operator+(T num, const Vec2<T>& v) {
  return v + num;
}

template <numeric T>
constexpr Vec2<T> operator-(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <numeric T>
constexpr Vec2<T> operator-(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x - num, v.y - num);
}

template <numeric T>
constexpr Vec2<T> operator-(T num, const Vec2<T>& v) {
  return v - num;
}

template <numeric T>
constexpr Vec2<T> operator*(const Vec2<T>& v1, const Vec2<T>& v2) {
  return Vec2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <numeric T>
constexpr Vec2<T> operator*(const Vec2<T>& v, T num) {
  return Vec2<T>(v.x * num, v.y * num);
}

template <numeric T>
constexpr Vec2<T> operator*(T num, const Vec2<T>& v) {
  return v * num;
}

template <numeric T>
constexpr Vec2<T> operator/(const Vec2<T>& v1, const Vec2<T>& v2) {
  if (v2.is_zero()) {
    throw std::runtime_error("Cannot divide by zero 2D vector");
  }
  return Vec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <numeric T>
constexpr Vec2<T> operator/(const Vec2<T>& v, T num) {
  if (num == T{0}) {
    throw std::runtime_error("Cannot divide by zero number");
  }
  return Vec2<T>(v.x / num, v.y / num);
}

//--------------------------------------------
// Other vector operations
//--------------------------------------------

template <numeric T>
constexpr T dot(const Vec2<T>& v1, const Vec2<T>& v2) {
  auto v = v1 * v2;
  return v.x + v.y;
}

template <numeric T>
constexpr Vec2<T> normalized(const Vec2<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    l += static_cast<T>(1E-6);
  }
  return Vec2<T>{static_cast<T>(v.x / l), static_cast<T>(v.y / l)};
}
