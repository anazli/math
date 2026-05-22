#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

#include "types.h"

template <numeric T>
class Vec3;

template <numeric T>
class Point3;

template <numeric T>
class Normal3;

template <numeric T>
class Vec4 {
 public:
  Vec4() = default;
  Vec4(T p1, T p2, T p3, T p4) : x{p1}, y{p2}, z{p3}, w{p4} {}
  explicit Vec4(const Vec3<T>& v) : x{v.x}, y{v.y}, z{v.z}, w{0} {}
  explicit Vec4(const Point3<T>& p) : x{p.x}, y{p.y}, z{p.z}, w{1} {}
  explicit Vec4(const Normal3<T>& n) : x{n.x}, y{n.y}, z{n.z}, w{0} {}

  static Vec4<T> create_unit_vec() { return Vec4<T>(T{1}, T{1}, T{1}, T{1}); }

  void set(T n) { x = y = z = w = n; }
  void set(T xVal, T yVal, T zVal, T wVal) {
    x = xVal;
    y = yVal;
    z = zVal;
    w = wVal;
  }

  T operator[](int i) const {
    if (i < 0 || i > 3) throw std::out_of_range("Index out of range");
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    return w;
  }

  T& operator[](int i) {
    if (i < 0 || i > 3) throw std::out_of_range("Index out of range");
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    return w;
  }

  Vec4<T>& operator=(const Vec3<T>& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = T{0};
    return *this;
  }

  Vec4<T>& operator=(const Point3<T>& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    w = T{1};
    return *this;
  }

  auto operator<=>(const Vec4<T>&) const = default;

  Vec4<T> operator+() const { return Vec4<T>(x, y, z, w); };
  Vec4<T> operator-() const { return Vec4<T>(-x, -y, -z, -w); }

  void normalize() {
    auto l = length();
    if (l < std::numeric_limits<double>::epsilon()) {
      l += static_cast<T>(1E-6);
    }
    x = static_cast<T>(x / l);
    y = static_cast<T>(y / l);
    z = static_cast<T>(z / l);
    w = static_cast<T>(w / l);
  }

  auto length() const {
    return static_cast<T>(sqrt(x * x + y * y + z * z + w * w));
  }

  bool is_zero() const { return *this == Vec4<T>(T{0}, T{0}, T{0}, T{0}); }

  void zero() {
    x = T{0};
    y = T{0};
    z = T{0};
    w = T{0};
  }

 public:
  T x = T{0};
  T y = T{0};
  T z = T{0};
  T w = T{0};
};

using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
std::istream& operator>>(std::istream& in, Vec4<T>& v) {
  T x, y, z, w;
  in >> x >> y >> z >> w;
  v.set(x, y, z, w);
  return in;
}

template <numeric T>
std::ostream& operator<<(std::ostream& out, const Vec4<T>& v) {
  out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
  return out;
}

template <numeric T>
Vec4<T> operator+(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <numeric T>
Vec4<T> operator+(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x + num, v.y + num, v.z + num, v.w + num);
}

template <numeric T>
Vec4<T> operator+(T num, const Vec4<T>& v) {
  return v + num;
}

template <numeric T>
Vec4<T> operator-(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <numeric T>
Vec4<T> operator-(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x - num, v.y - num, v.z - num, v.w - num);
}

template <numeric T>
Vec4<T> operator-(T num, const Vec4<T>& v) {
  return v - num;
}

template <numeric T>
Vec4<T> operator*(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <numeric T>
Vec4<T> operator*(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x * num, v.y * num, v.z * num, v.w * num);
}

template <numeric T>
Vec4<T> operator*(T num, const Vec4<T>& v) {
  return v * num;
}

template <numeric T>
Vec4<T> operator/(const Vec4<T>& v1, const Vec4<T>& v2) {
  if (v2.is_zero()) {
    throw std::runtime_error("Cannot divide by zero 4D vector");
  }
  return Vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <numeric T>
Vec4<T> operator/(const Vec4<T>& v, T num) {
  if (num == T{0}) {
    throw std::runtime_error("Cannot divide by zero number");
  }
  return Vec4<T>(v.x / num, v.y / num, v.z / num, v.w / num);
}

template <numeric T>
auto dot(const Vec4<T>& v1, const Vec4<T>& v2) {
  Vec4<T> v = v1 * v2;
  return v.x + v.y + v.z + v.w;
}

template <numeric T>
Vec4<T> normalized(const Vec4<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    l += static_cast<T>(1E-6);
  }
  return v / static_cast<T>(l);
}
