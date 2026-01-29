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
  Normal3() = default;
  Normal3(T p1, T p2, T p3) : m_x{p1}, m_y{p2}, m_z{p3} {}
  explicit Normal3(const Vec4<T>& v) : m_x{v.x()}, m_y{v.y()}, m_z{v.z()} {}
  explicit Normal3(const Point3<T>& p) : m_x{p.x()}, m_y{p.y()}, m_z{p.z()} {}
  explicit Normal3(const Vec3<T>& v) : m_x{v.x()}, m_y{v.y()}, m_z{v.z()} {}

  T x() const { return m_x; }
  T y() const { return m_y; }
  T z() const { return m_z; }

  void x(T x) { m_x = x; }
  void y(T y) { m_y = y; }
  void z(T z) { m_z = z; }
  void set(T n) { m_x = m_y = m_z = n; }
  void set(T x, T y, T z) {
    m_x = x;
    m_y = y;
    m_z = z;
  }

  T operator[](int i) const {
    assert(i >= 0 && i <= 2);
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    return m_z;
  }

  T& operator[](int i) {
    assert(i >= 0 && i <= 2);
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    return m_z;
  }

  Normal3<T>& operator=(const Vec4<T>& v) {
    m_x = v.x();
    m_y = v.y();
    m_z = v.z();
    return *this;
  }

  auto operator<=>(const Normal3<T>&) const = default;

  Normal3<T> operator+() const { return Normal3<T>(m_x, m_y, m_z); };
  Normal3<T> operator-() const { return Normal3<T>(-m_x, -m_y, -m_z); }

  auto length() const {
    return static_cast<T>(sqrt(x() * x() + y() * y() + z() * z()));
  }

 private:
  T m_x = T{1};
  T m_y = T{1};
  T m_z = T{1};
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
  out << "(" << n.x() << "," << n.y() << "," << n.z() << ")" << std::endl;
  return out;
}

//----------------------------------------------
// Overloaded math operators as normal functions
//----------------------------------------------

template <numeric T>
Normal3<T> operator+(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x() + n2.x(), n1.y() + n2.y(), n1.z() + n2.z());
}

template <numeric T>
Normal3<T> operator+(const Normal3<T>& n, const Vec3<T>& v) {
  return Vec3<T>(n.x() + v.x(), n.y() + v.y(), n.z() + v.z());
}

template <numeric T>
Normal3<T> operator+(const Vec3<T>& v, const Normal3<T>& n) {
  return n + v;
}

template <numeric T>
Normal3<T> operator+(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x() + num, n.y() + num, n.z() + num);
}

template <numeric T>
Normal3<T> operator+(T num, const Normal3<T>& v) {
  return v + num;
}

template <numeric T>
Normal3<T> operator-(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x() - n2.x(), n1.y() - n2.y(), n1.z() - n2.z());
}

template <numeric T>
Normal3<T> operator-(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x() - num, n.y() - num, n.z() - num);
}

template <numeric T>
Normal3<T> operator-(T num, const Normal3<T>& n) {
  return n - num;
}

template <numeric T>
Normal3<T> operator*(const Normal3<T>& n1, const Normal3<T>& n2) {
  return Normal3<T>(n1.x() * n2.x(), n1.y() * n2.y(), n1.z() * n2.z());
}

template <numeric T>
Normal3<T> operator*(const Normal3<T>& n, const Vec3<T>& v) {
  return Normal3<T>(n.x() * v.x(), n.y() * v.y(), n.z() * v.z());
}

template <numeric T>
Normal3<T> operator*(const Vec3<T>& v, const Normal3<T>& n) {
  return n * v;
}

template <numeric T>
Normal3<T> operator*(const Normal3<T>& n, T num) {
  return Normal3<T>(n.x() * num, n.y() * num, n.z() * num);
}

template <numeric T>
Normal3<T> operator*(T num, const Normal3<T>& n) {
  return n * num;
}

template <numeric T>
T dot(const Normal3<T>& n1, const Normal3<T>& n2) {
  Normal3<T> n = n1 * n2;
  return n.x() + n.y() + n.z();
}

template <numeric T>
T dot(const Normal3<T>& n, const Vec3<T>& v) {
  Normal3<T> u = n * v;
  return u.x() + u.y() + u.z();
}

template <numeric T>
T dot(const Vec3<T>& v, const Normal3<T>& n) {
  return dot(n, v);
}

template <numeric T>
Normal3<T> normalized(const Normal3<T>& v) {
  auto l = v.length();
  if (l < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error("Cannot normalize zero-length 3D normal");
  }
  return v / static_cast<T>(l);
}