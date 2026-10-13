#pragma once

#include <cassert>
#include <iostream>

#include "types.h"
#include "vec2.h"

template <numeric T>
class Vec2;

template <numeric T>
class Mat2 {
 public:
  // Column-major flat array: data[0] = m00, data[1] = m10, data[2] = m01,
  // data[3] = m11
  alignas(sizeof(T) * 4) T data[4] = {T{1}, T{0}, T{0}, T{1}};

  constexpr Mat2() = default;

  constexpr Mat2(T num) {
    data[0] = num;
    data[1] = num;
    data[2] = num;
    data[3] = num;
  }

  constexpr Mat2(const Vec2<T>& row1, const Vec2<T>& row2) {
    data[0] = row1.x;
    data[1] = row2.x;
    data[2] = row1.y;
    data[3] = row2.y;
  }

  // Get element at (row, col)
  constexpr T get(int row, int col) const {
    assert(row >= 0 && row < 2 && col >= 0 && col < 2);
    return data[col * 2 + row];
  }

  // Set element at (row, col)
  constexpr void set(int row, int col, T val) {
    assert(row >= 0 && row < 2 && col >= 0 && col < 2);
    data[col * 2 + row] = val;
  }

  // Return row as Vec2
  constexpr Vec2<T> operator[](int i) const {
    assert(i >= 0 && i <= 1);
    return Vec2<T>(data[i], data[i + 2]);
  }

  constexpr double determinant() const {
    // data[0] = m00, data[1] = m10, data[2] = m01, data[3] = m11
    // det = m00 * m11 - m01 * m10
    return data[0] * data[3] - data[2] * data[1];
  }
};

using Mat2D = Mat2<float>;

template <numeric T>
constexpr Mat2<T> operator+(const Mat2<T>& m1, const Mat2<T>& m2) {
  Mat2<T> ret;
  ret.data[0] = m1.data[0] + m2.data[0];
  ret.data[1] = m1.data[1] + m2.data[1];
  ret.data[2] = m1.data[2] + m2.data[2];
  ret.data[3] = m1.data[3] + m2.data[3];
  return ret;
}

template <numeric T>
constexpr Mat2<T> operator+(const Mat2<T>& m1, T num) {
  Mat2<T> ret;
  ret.data[0] = m1.data[0] + num;
  ret.data[1] = m1.data[1] + num;
  ret.data[2] = m1.data[2] + num;
  ret.data[3] = m1.data[3] + num;
  return ret;
}

template <numeric T>
constexpr Mat2<T> operator-(const Mat2<T>& m1, const Mat2<T>& m2) {
  Mat2<T> ret;
  ret.data[0] = m1.data[0] - m2.data[0];
  ret.data[1] = m1.data[1] - m2.data[1];
  ret.data[2] = m1.data[2] - m2.data[2];
  ret.data[3] = m1.data[3] - m2.data[3];
  return ret;
}

template <numeric T>
constexpr Mat2<T> operator-(const Mat2<T>& m1, T num) {
  Mat2<T> ret;
  ret.data[0] = m1.data[0] - num;
  ret.data[1] = m1.data[1] - num;
  ret.data[2] = m1.data[2] - num;
  ret.data[3] = m1.data[3] - num;
  return ret;
}

template <numeric T>
constexpr Mat2<T> operator*(const Mat2<T>& m1, T num) {
  Mat2<T> ret;
  ret.data[0] = m1.data[0] * num;
  ret.data[1] = m1.data[1] * num;
  ret.data[2] = m1.data[2] * num;
  ret.data[3] = m1.data[3] * num;
  return ret;
}

template <numeric T>
constexpr Mat2<T> operator*(const Mat2<T>& m1, const Mat2<T>& m2) {
  Mat2<T> ret;
  for (int col = 0; col < 2; ++col) {
    for (int row = 0; row < 2; ++row) {
      ret.set(
          row, col,
          m1.get(row, 0) * m2.get(0, col) + m1.get(row, 1) * m2.get(1, col));
    }
  }
  return ret;
}

template <numeric T>
std::ostream& operator<<(std::ostream& out, const Mat2<T>& m) {
  out << "{" << m[0] << "," << m[1] << "}";
  return out;
}
