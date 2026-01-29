#pragma once

#include <iostream>
#include <random>

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
  Vec4(T p1, T p2, T p3, T p4) : m_x{p1}, m_y{p2}, m_z{p3}, m_w{p4} {}
  explicit Vec4(const Vec3<T>& v)
      : m_x{v.x()}, m_y{v.y()}, m_z(v.z()), m_w{0} {}
  explicit Vec4(const Point3<T>& p)
      : m_x{p.x()}, m_y{p.y()}, m_z{p.z()}, m_w{1} {}
  explicit Vec4(const Normal3<T>& n)
      : m_x{n.x()}, m_y{n.y()}, m_z{n.z()}, m_w{0} {}

  static Vec4<T> create_unit_vec() { return Vec4<T>(T{1}, T{1}, T{1}, T{1}); }

  T x() const { return m_x; }
  T y() const { return m_y; }
  T z() const { return m_z; }
  T w() const { return m_w; }

  void x(T x) { m_x = x; }
  void y(T y) { m_y = y; }
  void z(T z) { m_z = z; }
  void w(T w) { m_w = w; }
  void set(T n) { m_x = m_y = m_z = m_w = n; }
  void set(T x, T y, T z, T w) {
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
  }

  T operator[](int i) const {
    if (i < 0 || i > 3) throw std::out_of_range("Index out of range");
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    if (i == 2) return m_z;
    return m_w;
  }

  T& operator[](int i) {
    if (i < 0 || i > 3) throw std::out_of_range("Index out of range");
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    if (i == 2) return m_z;
    return m_w;
  }

  Vec4<T>& operator=(const Vec3<T>& v) {
    m_x = v.x();
    m_y = v.y();
    m_z = v.z();
    m_w = T{0};
    return *this;
  }

  Vec4<T>& operator=(const Point3<T>& p) {
    m_x = p.x();
    m_y = p.y();
    m_z = p.z();
    m_w = T{1};
    return *this;
  }

  auto operator<=>(const Vec4<T>&) const = default;

  Vec4<T> operator+() const { return Vec4<T>(m_x, m_y, m_z, m_w); };
  Vec4<T> operator-() const { return Vec4<T>(-m_x, -m_y, -m_z, -m_w); }

  void normalize() {
    auto l = length();
    if (l < std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error("Cannot normalize zero-length 4D vector");
    }
    m_x = static_cast<T>(m_x / l);
    m_y = static_cast<T>(m_y / l);
    m_z = static_cast<T>(m_z / l);
    m_w = static_cast<T>(m_w / l);
  }

  auto length() const {
    return static_cast<T>(sqrt(x() * x() + y() * y() + z() * z() + w() * w()));
  }

  bool is_zero() const { return *this == Vec4<T>(T{0}, T{0}, T{0}, T{0}); }

  void zero() {
    m_x = T{0};
    m_y = T{0};
    m_z = T{0};
    m_w = T{0};
  }

 private:
  T m_x = T{0};
  T m_y = T{0};
  T m_z = T{0};
  T m_w = T{0};
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
  out << "(" << v.x() << "," << v.y() << "," << v.z() << "," << v.w() << ")";
  return out;
}

template <numeric T>
Vec4<T> operator+(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z(),
                 v1.w() + v2.w());
}

template <numeric T>
Vec4<T> operator+(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x() + num, v.y() + num, v.z() + num, v.w() + num);
}

template <numeric T>
Vec4<T> operator+(T num, const Vec4<T>& v) {
  return v + num;
}

template <numeric T>
Vec4<T> operator-(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z(),
                 v1.w() - v2.w());
}

template <numeric T>
Vec4<T> operator-(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x() - num, v.y() - num, v.z() - num, v.w() - num);
}

template <numeric T>
Vec4<T> operator-(T num, const Vec4<T>& v) {
  return v - num;
}

template <numeric T>
Vec4<T> operator*(const Vec4<T>& v1, const Vec4<T>& v2) {
  return Vec4<T>(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z(),
                 v1.w() * v2.w());
}

template <numeric T>
Vec4<T> operator*(const Vec4<T>& v, T num) {
  return Vec4<T>(v.x() * num, v.y() * num, v.z() * num, v.w() * num);
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
  return Vec4<T>(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z(),
                 v1.w() / v2.w());
}

template <numeric T>
Vec4<T> operator/(const Vec4<T>& v, T num) {
  if (num == T{0}) {
    throw std::runtime_error("Cannot divide by zero number");
  }
  return Vec4<T>(v.x() / num, v.y() / num, v.z() / num, v.w() / num);
}

template <numeric T>
auto dot(const Vec4<T>& v1, const Vec4<T>& v2) {
  Vec4<T> v = v1 * v2;
  return v.x() + v.y() + v.z() + v.w();
}

template <numeric T>
Vec4<T> normalized(const Vec4<T>& v) {
  return v / (v.length() + static_cast<T>(1.E-30));
}
