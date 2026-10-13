#pragma once

#include <sstream>

#include "types.h"

template <numeric T>
class Vec4;

template <numeric T>
class Vec3;

template <numeric T>
class Normal3;

template <numeric T>
class Point3 {
 public:
  constexpr Point3() = default;
  constexpr Point3(T x, T y, T z) : x{x}, y{y}, z{z} {}
  constexpr explicit Point3(const Vec4<T> &v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr explicit Point3(const Vec3<T> &v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr explicit Point3(const Normal3<T> &n) : x{n.x}, y{n.y}, z{n.z} {}

  constexpr void set(T n) { x = y = z = n; }
  constexpr void set(T xVal, T yVal, T zVal) {
    x = xVal;
    y = yVal;
    z = zVal;
  }

  constexpr Point3<T> &operator=(const Vec4<T> &vec4) {
    x = vec4.x;
    y = vec4.y;
    z = vec4.z;
    return *this;
  }

  constexpr auto operator<=>(const Point3<T> &) const = default;

  constexpr Point3<T> operator+(const Vec3<T> &v) const {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }

  constexpr Vec3<T> operator+(const Point3<T> &p) const {
    return Vec3<T>(x + p.x, y + p.y, z + p.z);
  }

  constexpr Point3<T> operator-(
      const Vec3<T> &v) const {  // Point - Vector = Point
    return Point3<T>(x - v.x, y - v.y, z - v.z);
  }

  constexpr Vec3<T> operator-(
      const Point3<T> &p) const {  // Point - Point = Vector
    return Vec3<T>(x - p.x, y - p.y, z - p.z);
  }

  constexpr bool is_zero() const {
    return *this == Point3<T>(T{0}, T{0}, T{0});
  }

 public:
  T x = T{0};
  T y = T{0};
  T z = T{0};
};

using Point3i = Point3<int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
std::stringstream &operator<<(std::stringstream &out, const Point3<T> &p) {
  out << "(" << p.x << "," << p.y << "," << p.z << ")";
  return out;
}

template <numeric T>
std::ostream &operator<<(std::ostream &out, const Point3<T> &p) {
  out << "(" << p.x << "," << p.y << "," << p.z << ")";
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
constexpr Vec3<T> operator-(const Vec3<T> &v, const Point3<T> &p) {
  return Vec3<T>(v.x - p.x, v.y - p.y, v.z - p.z);
}

template <numeric T>
constexpr Vec3<T> operator+(const Vec3<T> &v, const Point3<T> &p) {
  return Vec3<T>(v.x + p.x, v.y + p.y, v.z + p.z);
}

template <numeric T>
constexpr Point3<T> operator+(const Point3<T> &p, T num) {
  return Point3<T>(p.x + num, p.y + num, p.z + num);
}

template <numeric T>
constexpr Point3<T> operator*(const Point3<T> &p, T num) {
  return Point3<T>(p.x * num, p.y * num, p.z * num);
}

template <numeric T>
constexpr Point3<T> operator*(T num, const Point3<T> &p) {
  return p * num;
}
