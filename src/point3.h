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
  Point3() = default;
  Point3(T x, T y, T z) : m_x{x}, m_y{y}, m_z{z} {}
  explicit Point3(const Vec4<T> &v) : m_x{v.x()}, m_y{v.y()}, m_z{v.z()} {}
  explicit Point3(const Vec3<T> &v) : m_x{v.x()}, m_y{v.y()}, m_z{v.z()} {}
  explicit Point3(const Normal3<T> &n) : m_x{n.x()}, m_y{n.y()}, m_z{n.z()} {}

  T x() const { return m_x; }
  T y() const { return m_y; }
  T z() const { return m_z; }

  void x(T x) { m_x = x; }
  void y(T y) { m_y = y; }
  void z(T z) { m_z = z; }
  void set(T n) { m_x = m_y = m_z = n; }

  T operator[](int i) const {
    if (i < 0 || i > 2) throw std::out_of_range("Index out of range");
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    return m_z;
  }

  T &operator[](int i) {
    if (i < 0 || i > 2) throw std::out_of_range("Index out of range");
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    return m_z;
  }

  Point3<T> &operator=(const Vec4<T> &vec4) {
    m_x = vec4.x();
    m_y = vec4.y();
    m_z = vec4.z();
    return *this;
  }

  auto operator<=>(const Point3<T> &) const = default;

  Point3<T> operator+(const Vec3<T> &v) const {
    return Point3<T>(m_x + v.x(), m_y + v.y(), m_z + v.z());
  }

  Vec3<T> operator+(const Point3<T> &p) const {
    return Vec3<T>(m_x + p.m_x, m_y + p.m_y, m_z + p.m_z);
  }

  Point3<T> operator-(const Vec3<T> &v) const {  // Point - Vector = Point
    return Point3<T>(m_x - v.x(), m_y - v.y(), m_z - v.z());
  }

  Vec3<T> operator-(const Point3<T> &p) const {  // Point - Point = Vector
    return Vec3<T>(m_x - p.m_x, m_y - p.m_y, m_z - p.m_z);
  }

  bool is_zero() const { return *this == Point3<T>(T{0}, T{0}, T{0}); }

 private:
  T m_x = T{0};
  T m_y = T{0};
  T m_z = T{0};
};

using Point3i = Point3<int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

//--------------------------------------------
// Overloaded I/O operators (input, output)
//--------------------------------------------

template <numeric T>
std::stringstream &operator<<(std::stringstream &out, const Point3<T> &p) {
  out << "(" << p.x() << "," << p.y() << "," << p.z() << ")";
  return out;
}

template <numeric T>
std::ostream &operator<<(std::ostream &out, const Point3<T> &p) {
  out << "(" << p.x() << "," << p.y() << "," << p.z() << ")";
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
Vec3<T> operator-(const Vec3<T> &v, const Point3<T> &p) {
  return Vec3<T>(v.x() - p.x(), v.y() - p.y(), v.z() - p.z());
}

template <numeric T>
Vec3<T> operator+(const Vec3<T> &v, const Point3<T> &p) {
  return Vec3<T>(v.x() + p.x(), v.y() + p.y(), v.z() + p.z());
}

template <numeric T>
Point3<T> operator+(const Point3<T> &p, T num) {
  return Point3<T>(p.x() + num, p.y() + num, p.z() + num);
}

template <numeric T>
Point3<T> operator*(const Point3<T> &p, T num) {
  return Point3<T>(p.x() * num, p.y() * num, p.z() * num);
}

template <numeric T>
Point3<T> operator*(T num, const Point3<T> &p) {
  return p * num;
}
