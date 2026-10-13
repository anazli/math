#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "types.h"

template <numeric T>
class Vec4;

template <numeric T>
class Vec3;

template <numeric T>
class Point3;

template <numeric T>
class Normal3 {
 public:
  constexpr Normal3() = default;
  constexpr Normal3(T p1, T p2, T p3) : x{p1}, y{p2}, z{p3} {}
  constexpr explicit Normal3(const Vec4<T>& v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr explicit Normal3(const Point3<T>& p) : x{p.x}, y{p.y}, z{p.z} {}
  constexpr explicit Normal3(const Vec3<T>& v) : x{v.x}, y{v.y}, z{v.z} {}

  constexpr void set(T n) { x = y = z = n; }
  constexpr void set(T xVal, T yVal, T zVal) {
    x = xVal;
    y = yVal;
    z = zVal;
  }

  constexpr Normal3<T>& operator=(const Vec4<T>& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  constexpr auto operator<=>(const Normal3<T>&) const = default;

  constexpr Normal3<T> operator+() const { return Normal3<T>(x, y, z); };
  constexpr Normal3<T> operator-() const { return Normal3<T>(-x, -y, -z); }

  constexpr auto length() const {
    return static_cast<T>(sqrt(x * x + y * y + z * z));
  }

 public:
  T x = T{1};
  T y = T{1};
  T z = T{1};
};

using Normal3i = Normal3<int>;
using Normal3f = Normal3<float>;
using Normal3d = Normal3<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
inline std::istream& operator>>(std::istream& in, Normal3<T>& n) {
  T x, y, z;
  in >> x >> y >> z;
  n.set(x, y, z);
  return in;
}

template <numeric T>
inline std::ostream& operator<<(std::ostream& out, const Normal3<T>& n) {
  out << "(" << n.x << "," << n.y << "," << n.z << ")" << std::endl;
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
constexpr Normal3<T> operator+(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x + n2.x, n1.y + n2.y, n1.z + n2.z);
}

template <numeric T>
constexpr Vec3<T> operator+(const Normal3<T>& n, const Vec3<T>& v) {
  return Vec3<T>(n.x + v.x, n.y + v.y, n.z + v.z);
}

template <numeric T>
constexpr Vec3<T> operator+(const Vec3<T>& v, const Normal3<T>& n) {
  return n + v;
}

template <numeric T>
constexpr Normal3<T> operator+(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x + num, n.y + num, n.z + num);
}

template <numeric T>
constexpr Normal3<T> operator+(T num, const Normal3<T>& v) {
  return v + num;
}

template <numeric T>
constexpr Normal3<T> operator-(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x - n2.x, n1.y - n2.y, n1.z - n2.z);
}

template <numeric T>
constexpr Normal3<T> operator-(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x - num, n.y - num, n.z - num);
}

template <numeric T>
constexpr Normal3<T> operator-(T num, const Normal3<T>& n) {
  return n - num;
}

template <numeric T>
constexpr Normal3<T> operator*(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x * n2.x, n1.y * n2.y, n1.z * n2.z);
}

template <numeric T>
constexpr Normal3<T> operator*(const Normal3<T>& n, const Vec3<T>& v) {
  return Normal3<T>(n.x * v.x, n.y * v.y, n.z * v.z);
}

template <numeric T>
constexpr Normal3<T> operator*(const Vec3<T>& v, const Normal3<T>& n) {
  return n * v;
}

template <numeric T>
constexpr Normal3<T> operator*(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x * num, n.y * num, n.z * num);
}

template <numeric T>
constexpr Normal3<T> operator*(T num, const Normal3<T>& n) {
  return n * num;
}

template <numeric T>
constexpr Normal3<T> operator/(const Normal3<T>& n1, const Normal3<T>& n2) {
  auto d = n2 + static_cast<T>(1.E-30);
  return Normal3<T>(n1.x / d.x, n1.y / d.y, n1.z / d.z);
}

template <numeric T>
constexpr Normal3<T> operator/(const Normal3<T>& n, T num) {
  num += 1.E-30;
  return Normal3<T>(n.x / num, n.y / num, n.z / num);
}

template <numeric T>
constexpr T dot(const Normal3<T>& n1, const Normal3<T>& n2) {
  Normal3<T> n = n1 * n2;
  return n.x + n.y + n.z;
}

template <numeric T>
constexpr T dot(const Normal3<T>& n, const Vec3<T>& v) {
  Normal3<T> u = n * v;
  return u.x + u.y + u.z;
}

template <numeric T>
constexpr T dot(const Vec3<T>& v, const Normal3<T>& n) {
  return dot(n, v);
}

template <numeric T>
constexpr Normal3<T> normalized(const Normal3<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error("Cannot normalize zero-length 3D normal");
  }
  return v / static_cast<T>(l);
}