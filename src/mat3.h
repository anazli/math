#pragma once
#include <cassert>
#include <cmath>
#include <iostream>

#include "mat2.h"
#include "types.h"
#include "vec3.h"

template <numeric T>
class Vec3;

template <numeric T>
class Mat2;

template <numeric T>
class Mat3 {
 public:
  // Column-major flat array: 16 elements (3x3 padded to 4x4 for SIMD)
  // Column 0: data[0]=m00, data[1]=m10, data[2]=m20, data[3]=unused
  // Column 1: data[4]=m01, data[5]=m11, data[6]=m21, data[7]=unused
  // Column 2: data[8]=m02, data[9]=m12, data[10]=m22, data[11]=unused
  // Column 3: data[12..15]=unused
  alignas(16) T data[16];

  Mat3() {
    // Initialize to identity matrix
    for (int i = 0; i < 16; ++i) data[i] = T{0};
    data[0] = T{1};
    data[5] = T{1};
    data[10] = T{1};
  }

  Mat3(T num) {
    for (int i = 0; i < 16; ++i) {
      data[i] = (i % 4 == 3 || i >= 12) ? T{0} : num;
    }
  }

  Mat3(const Vec3<T>& row0, const Vec3<T>& row1, const Vec3<T>& row2) {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
    data[0] = row0.x;
    data[1] = row1.x;
    data[2] = row2.x;
    data[4] = row0.y;
    data[5] = row1.y;
    data[6] = row2.y;
    data[8] = row0.z;
    data[9] = row1.z;
    data[10] = row2.z;
  }

  // Get element at (row, col) - only for 0..2 range
  T get(int row, int col) const {
    assert(row >= 0 && row < 3 && col >= 0 && col < 3);
    return data[col * 4 + row];
  }

  // Set element at (row, col) - only for 0..2 range
  void set(int row, int col, T val) {
    assert(row >= 0 && row < 3 && col >= 0 && col < 3);
    data[col * 4 + row] = val;
  }

  // Return row as Vec3
  Vec3<T> operator[](int i) const {
    assert(i >= 0 && i <= 2);
    return Vec3<T>(data[i], data[4 + i], data[8 + i]);
  }

  T trace() const;

  void zero() {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
  }

  void identity() {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
    data[0] = T{1};
    data[5] = T{1};
    data[10] = T{1};
  }

  T determinant() const;
  Mat2<T> minor(int i, int j) const;
  Mat3<T> inverse() const;
  Mat3<T> transpose() const;
  T coFactor(int i, int j) const {
    T sign = ((i + j) % 2 == 0) ? T{1} : T{-1};
    return sign * minor(i, j).determinant();
  }
};

using Mat3D = Mat3<float>;

template <numeric T>
T Mat3<T>::trace() const {
  return data[0] + data[5] + data[10];
}

template <numeric T>
T Mat3<T>::determinant() const {
  // Using 3x3 submatrix of padded layout
  T r1 = data[0] * (data[5] * data[10] - data[6] * data[9]);
  T r2 = data[1] * (data[4] * data[10] - data[6] * data[8]);
  T r3 = data[2] * (data[4] * data[9] - data[5] * data[8]);
  return r1 - r2 + r3;
}

template <numeric T>
Mat2<T> Mat3<T>::minor(int i, int j) const {
  Mat2<T> mi;
  int rr = 0;
  for (int row = 0; row < 3; ++row) {
    if (row == i) continue;
    int cc = 0;
    for (int col = 0; col < 3; ++col) {
      if (col == j) continue;
      mi.set(rr, cc, get(row, col));
      cc++;
    }
    rr++;
  }
  return mi;
}

template <numeric T>
Mat3<T> Mat3<T>::inverse() const {
  Mat3<T> inv;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      inv.set(j, i, coFactor(i, j));
    }
  }

  T det = determinant();
  T invDet = 1. / det;
  inv = inv * invDet;
  return inv;
}

template <numeric T>
Mat3<T> Mat3<T>::transpose() const {
  Mat3<T> ret;
  ret.set(0, 0, get(0, 0));
  ret.set(1, 0, get(0, 1));
  ret.set(2, 0, get(0, 2));

  ret.set(0, 1, get(1, 0));
  ret.set(1, 1, get(1, 1));
  ret.set(2, 1, get(1, 2));

  ret.set(0, 2, get(2, 0));
  ret.set(1, 2, get(2, 1));
  ret.set(2, 2, get(2, 2));

  return ret;
}

template <numeric T>
Mat3<T> operator+(const Mat3<T>& m1, const Mat3<T>& m2) {
  Mat3<T> ret;
  for (int i = 0; i < 12; ++i) ret.data[i] = m1.data[i] + m2.data[i];
  return ret;
}

template <numeric T>
Mat3<T> operator+(const Mat3<T>& m1, T num) {
  Mat3<T> ret;
  for (int i = 0; i < 12; ++i) ret.data[i] = m1.data[i] + num;
  return ret;
}

template <numeric T>
Mat3<T> operator-(const Mat3<T>& m1, const Mat3<T>& m2) {
  Mat3<T> ret;
  for (int i = 0; i < 12; ++i) ret.data[i] = m1.data[i] - m2.data[i];
  return ret;
}

template <numeric T>
Mat3<T> operator-(const Mat3<T>& m1, T num) {
  Mat3<T> ret;
  for (int i = 0; i < 12; ++i) ret.data[i] = m1.data[i] - num;
  return ret;
}

template <numeric T>
Mat3<T> operator*(const Mat3<T>& m1, const Mat3<T>& m2) {
  Mat3<T> ret;

  // Column-major matrix multiplication
  for (int col = 0; col < 3; ++col) {
    for (int row = 0; row < 3; ++row) {
      T sum = T{0};
      for (int k = 0; k < 3; ++k) {
        sum += m1.get(row, k) * m2.get(k, col);
      }
      ret.set(row, col, sum);
    }
  }

  return ret;
}

template <numeric T>
Mat3<T> operator*(const Mat3<T>& m1, T num) {
  Mat3<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] * num;
  return ret;
}

template <numeric T>
std::ostream& operator<<(std::ostream& out, const Mat3<T>& m) {
  out << "{" << m[0] << "," << m[1] << "," << m[2] << "}";
  return out;
}
