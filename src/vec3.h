#pragma once

#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>

#include "types.h"

template <numeric T>
class Vec4;

template <numeric T>
class Point3;

template <numeric T>
class Normal3;

template <numeric T>
class Vec3 {
 public:
  constexpr Vec3() = default;
  constexpr Vec3(T p1, T p2, T p3) : x{p1}, y{p2}, z{p3} {}
  constexpr explicit Vec3(const Vec4<T>& v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr explicit Vec3(const Point3<T>& v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr explicit Vec3(const Normal3<T>& n) : x{n.x}, y{n.y}, z{n.z} {}

  static constexpr Vec3<T> create_unit_vec() {
    return Vec3<T>(T{1}, T{1}, T{1});
  }

  constexpr Vec3<T>& operator=(const Vec4<T>& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  constexpr auto operator<=>(const Vec3<T>&) const = default;

  constexpr Vec3<T> operator+() const { return Vec3<T>(x, y, z); };
  constexpr Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

  constexpr void normalize() {
    auto l = length();
    if (l < std::numeric_limits<double>::epsilon()) {
      l += static_cast<T>(1E-6);
    }
    x = static_cast<T>(x / l);
    y = static_cast<T>(y / l);
    z = static_cast<T>(z / l);
  }

  constexpr T operator[](int i) const {
    if (i < 0 || i > 2) throw std::out_of_range("Index out of range");
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }

  constexpr T& operator[](int i) {
    if (i < 0 || i > 2) throw std::out_of_range("Index out of range");
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }

  constexpr auto length() const {
    return static_cast<T>(sqrt(x * x + y * y + z * z));
  }

  constexpr bool is_zero() const { return *this == Vec3<T>(T{0}, T{0}, T{0}); }

  constexpr void zero() {
    x = T{0};
    y = T{0};
    z = T{0};
  }

 public:
  T x = T{0};
  T y = T{0};
  T z = T{0};
};

using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
inline std::istream& operator>>(std::istream& in, Vec3<T>& v) {
  T x, y, z;
  in >> x >> y >> z;
  v.x = x;
  v.y = y;
  v.z = z;
  return in;
}

template <numeric T>
inline std::ostream& operator<<(std::ostream& out, const Vec3<T>& v) {
  out << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
constexpr Vec3<T> operator+(const Vec3<T>& v1, const Vec3<T>& v2) {
  return Vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <numeric T>
constexpr Vec3<T> operator+(const Vec3<T>& v, T num) {
  return Vec3<T>(v.x + num, v.y + num, v.z + num);
}

template <numeric T>
constexpr Vec3<T> operator+(T num, const Vec3<T>& v) {
  return v + num;
}

template <numeric T>
constexpr Vec3<T> operator-(const Vec3<T>& v1, const Vec3<T>& v2) {
  return Vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <numeric T>
constexpr Vec3<T> operator-(const Vec3<T>& v, T num) {
  return Vec3<T>(v.x - num, v.y - num, v.z - num);
}

template <numeric T>
constexpr Vec3<T> operator-(T num, const Vec3<T>& v) {
  return v - num;
}

template <numeric T>
constexpr Vec3<T> operator*(const Vec3<T>& v1, const Vec3<T>& v2) {
  return Vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <numeric T>
constexpr Vec3<T> operator*(const Vec3<T>& v, T num) {
  return Vec3<T>(v.x * num, v.y * num, v.z * num);
}

template <numeric T>
constexpr Vec3<T> operator*(T num, const Vec3<T>& v) {
  return v * num;
}

template <numeric T>
constexpr Vec3<T> operator/(const Vec3<T>& v1, const Vec3<T>& v2) {
  if (v2.is_zero()) {
    throw std::runtime_error("Cannot divide by zero 3D vector");
  }
  return Vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <numeric T>
constexpr Vec3<T> operator/(const Vec3<T>& v, T num) {
  if (num == T{0}) {
    throw std::runtime_error("Cannot divide by zero number");
  }
  return Vec3<T>(v.x / num, v.y / num, v.z / num);
}

//--------------------------------------------
// Other vector operations
//--------------------------------------------

template <numeric T>
constexpr auto dot(const Vec3<T>& v1, const Vec3<T>& v2) {
  Vec3<T> v = v1 * v2;
  return v.x + v.y + v.z;
}

template <numeric T>
constexpr Vec3<T> cross(const Vec3<T>& v1, const Vec3<T>& v2) {
  T x = v1.y * v2.z - v1.z * v2.y;
  T y = v1.z * v2.x - v1.x * v2.z;
  T z = v1.x * v2.y - v1.y * v2.x;
  return Vec3<T>(x, y, z);
}

template <numeric T>
constexpr Vec3<T> normalized(const Vec3<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    l += static_cast<T>(1E-6);
  }
  return v / static_cast<T>(l);
}

template <numeric T>
constexpr Vec3<T> reflect(const Vec3<T>& in, const Vec3<T>& normal) {
  return in - normal * T{2} * dot(in, normal);
}
