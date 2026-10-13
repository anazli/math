#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

#include "constants.h"
#include "mat3.h"
#include "types.h"
#include "vec4.h"

template <numeric T>
class Vec4;

template <numeric T>
class Vec3;

template <numeric T>
class Point3;

template <numeric T>
class Mat2;

template <numeric T>
class Mat3;

template <numeric T>
class Mat4 {
 public:
  // Column-major flat array: 16 elements
  // Column 0: data[0]=m00, data[1]=m10, data[2]=m20, data[3]=m30
  // Column 1: data[4]=m01, data[5]=m11, data[6]=m21, data[7]=m31
  // Column 2: data[8]=m02, data[9]=m12, data[10]=m22, data[11]=m32
  // Column 3: data[12]=m03, data[13]=m13, data[14]=m23, data[15]=m33
  alignas(16) T data[16];

  constexpr Mat4() {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
    data[0] = T{1};
    data[5] = T{1};
    data[10] = T{1};
    data[15] = T{1};
  }

  constexpr Mat4(T num) {
    for (int i = 0; i < 16; ++i) data[i] = num;
  }

  constexpr Mat4(const Vec4<T>& row0, const Vec4<T>& row1, const Vec4<T>& row2,
                 const Vec4<T>& row3) {
    data[0] = row0.x;
    data[1] = row1.x;
    data[2] = row2.x;
    data[3] = row3.x;
    data[4] = row0.y;
    data[5] = row1.y;
    data[6] = row2.y;
    data[7] = row3.y;
    data[8] = row0.z;
    data[9] = row1.z;
    data[10] = row2.z;
    data[11] = row3.z;
    data[12] = row0.w;
    data[13] = row1.w;
    data[14] = row2.w;
    data[15] = row3.w;
  }

  constexpr auto operator<=>(const Mat4<T>&) const = default;

  // Get element at (row, col)
  constexpr T get(int row, int col) const {
    assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return data[col * 4 + row];
  }

  // Set element at (row, col)
  constexpr void set(int row, int col, T val) {
    assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    data[col * 4 + row] = val;
  }

  // Return row as Vec4
  constexpr Vec4<T> operator[](int i) const {
    assert(i >= 0 && i <= 3);
    Vec4<T> ret;
    ret.x = data[i];
    ret.y = data[4 + i];
    ret.z = data[8 + i];
    ret.w = data[12 + i];
    return ret;
  }

  constexpr T trace() const;

  constexpr void zero() {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
  }

  constexpr void identity() {
    for (int i = 0; i < 16; ++i) data[i] = T{0};
    data[0] = T{1};
    data[5] = T{1};
    data[10] = T{1};
    data[15] = T{1};
  }

  constexpr T determinant() const;
  constexpr Mat3<T> minor(int i, int j) const;
  constexpr Mat4<T> inverse() const;
  constexpr Mat4<T> transpose() const;
  constexpr T coFactor(int i, int j) const {
    T sign = ((i + j) % 2 == 0) ? T{1} : T{-1};
    return sign * minor(i, j).determinant();
  }

  constexpr void Orient(const Vec3<T>& pos, const Vec3<T>& fwd,
                        const Vec3<T>& up);
  constexpr void LookAt(const Vec3<T>& pos, const Vec3<T>& lookAt,
                        const Vec3<T>& up);
};

using Mat4i = Mat4<int>;
using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

template <numeric T>
constexpr T Mat4<T>::trace() const {
  return data[0] + data[5] + data[10] + data[15];
}

template <numeric T>
constexpr T Mat4<T>::determinant() const {
  T det = T{0};
  // Change loop to iterate across row indices 'i' down Column 0
  for (int i = 0; i < 4; ++i) {
    det += get(i, 0) * coFactor(i, 0);
  }
  return det;
}

template <numeric T>
constexpr Mat3<T> Mat4<T>::minor(int i, int j) const {
  Mat3<T> mi;
  int rr = 0;
  for (int row = 0; row < 4; ++row) {  // Outer loop tracks rows
    if (row == i) continue;
    int cc = 0;
    for (int col = 0; col < 4; ++col) {  // Inner loop tracks columns
      if (col == j) continue;

      mi.set(rr, cc, get(row, col));  // Passes (row, col) correctly
      cc++;
    }
    rr++;
  }
  return mi;
}

template <numeric T>
constexpr Mat4<T> Mat4<T>::inverse() const {
  T det = determinant();
  assert(det != T{0});
  Mat4<T> inv;
  for (int i = 0; i < 4; ++i) {    // i = parent row index
    for (int j = 0; j < 4; ++j) {  // j = parent col index
      // Calculate cofactor using the correct matrix row/col, then transpose
      // into (j, i)
      inv.set(j, i, coFactor(i, j) / det);
    }
  }
  return inv;
}

template <numeric T>
constexpr Mat4<T> Mat4<T>::transpose() const {
  Mat4<T> ret;
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      ret.set(row, col, get(col, row));
    }
  }
  return ret;
}

template <numeric T>
constexpr void Mat4<T>::Orient(const Vec3<T>& pos, const Vec3<T>& fwd,
                               const Vec3<T>& up) {
  Vec3<T> left = up.cross(fwd);
  set(0, 0, fwd.x);
  set(0, 1, left.x);
  set(0, 2, up.x);
  set(0, 3, pos.x);
  set(1, 0, fwd.y);
  set(1, 1, left.y);
  set(1, 2, up.y);
  set(1, 3, pos.y);
  set(2, 0, fwd.z);
  set(2, 1, left.z);
  set(2, 2, up.z);
  set(2, 3, pos.z);
  set(3, 0, T{0});
  set(3, 1, T{0});
  set(3, 2, T{0});
  set(3, 3, T{1});
}

template <numeric T>
constexpr void Mat4<T>::LookAt(const Vec3<T>& pos, const Vec3<T>& lookAt,
                               const Vec3<T>& up) {
  Vec3<T> fwd = pos - lookAt;
  fwd.normalize();

  Vec3<T> right = up.cross(fwd);
  right.normalize();

  Vec3<T> up_norm = fwd.cross(right);
  up_norm.normalize();

  set(0, 0, right.x);
  set(0, 1, right.y);
  set(0, 2, right.z);
  set(0, 3, -dot(pos, right));
  set(1, 0, up_norm.x);
  set(1, 1, up_norm.y);
  set(1, 2, up_norm.z);
  set(1, 3, -dot(pos, up_norm));
  set(2, 0, fwd.x);
  set(2, 1, fwd.y);
  set(2, 2, fwd.z);
  set(2, 3, -dot(pos, fwd));
  set(3, 0, T{0});
  set(3, 1, T{0});
  set(3, 2, T{0});
  set(3, 3, T{1});
}

template <numeric T>
constexpr Mat4<T> operator+(const Mat4<T>& m1, const Mat4<T>& m2) {
  Mat4<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] + m2.data[i];
  return ret;
}

template <numeric T>
constexpr Mat4<T> operator+(const Mat4<T>& m1, T num) {
  Mat4<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] + num;
  return ret;
}

template <numeric T>
constexpr Mat4<T> operator-(const Mat4<T>& m1, const Mat4<T>& m2) {
  Mat4<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] - m2.data[i];
  return ret;
}

template <numeric T>
constexpr Mat4<T> operator-(const Mat4<T>& m1, T num) {
  Mat4<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] - num;
  return ret;
}

template <numeric T>
constexpr Mat4<T> operator*(const Mat4<T>& m1, const Mat4<T>& m2) {
  Mat4<T> ret;
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      T sum = T{0};
      for (int k = 0; k < 4; ++k) {
        sum += m1.get(row, k) * m2.get(k, col);
      }
      ret.set(row, col, sum);
    }
  }
  return ret;
}

template <numeric T>
constexpr Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v) {
  Vec4<T> ret;
  ret.x = m.get(0, 0) * v.x + m.get(0, 1) * v.y + m.get(0, 2) * v.z +
          m.get(0, 3) * v.w;
  ret.y = m.get(1, 0) * v.x + m.get(1, 1) * v.y + m.get(1, 2) * v.z +
          m.get(1, 3) * v.w;
  ret.z = m.get(2, 0) * v.x + m.get(2, 1) * v.y + m.get(2, 2) * v.z +
          m.get(2, 3) * v.w;
  ret.w = m.get(3, 0) * v.x + m.get(3, 1) * v.y + m.get(3, 2) * v.z +
          m.get(3, 3) * v.w;
  return ret;
}

template <numeric T>
constexpr Mat4<T> operator*(const Mat4<T>& m1, T num) {
  Mat4<T> ret;
  for (int i = 0; i < 16; ++i) ret.data[i] = m1.data[i] * num;
  return ret;
}

template <numeric T>
constexpr Mat4<T> translation(T x, T y, T z) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 3, x);
  ret.set(1, 3, y);
  ret.set(2, 3, z);
  return ret;
}

template <numeric T>
constexpr Mat4<T> translation(const Vec3<T>& v) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 3, v.x);
  ret.set(1, 3, v.y);
  ret.set(2, 3, v.z);
  return ret;
}

template <numeric T>
constexpr Mat4<T> scale(T x, T y, T z) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 0, x);
  ret.set(1, 1, y);
  ret.set(2, 2, z);
  return ret;
}

template <numeric T>
constexpr Mat4<T> scale(const Vec3<T>& v) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 0, v.x);
  ret.set(1, 1, v.y);
  ret.set(2, 2, v.z);
  return ret;
}

// TODO: floating point errors ~ E-8

template <numeric T>
constexpr Mat4<T> rotationOverX(T rad) {
  Mat4<T> ret;
  ret.identity();
  ret.set(1, 1, static_cast<T>(cos(rad)));
  ret.set(1, 2, -static_cast<T>(sin(rad)));
  ret.set(2, 1, static_cast<T>(sin(rad)));
  ret.set(2, 2, static_cast<T>(cos(rad)));
  return ret;
}

template <numeric T>
constexpr Mat4<T> rotationOverY(T rad) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 0, static_cast<T>(cos(rad)));
  ret.set(0, 2, static_cast<T>(sin(rad)));
  ret.set(2, 0, -static_cast<T>(sin(rad)));
  ret.set(2, 2, static_cast<T>(cos(rad)));
  return ret;
}

template <numeric T>
constexpr Mat4<T> rotationOverZ(T rad) {
  Mat4<T> ret;
  ret.identity();
  ret.set(0, 0, static_cast<T>(cos(rad)));
  ret.set(0, 1, -static_cast<T>(sin(rad)));
  ret.set(1, 0, static_cast<T>(sin(rad)));
  ret.set(1, 1, static_cast<T>(cos(rad)));
  return ret;
}

template <numeric T>
constexpr Mat4<T> view_transform(const Point3<T>& from, const Point3<T>& to,
                                 const Vec3<T>& up) {
  Vec3<T> forward = normalized(to - from);
  Vec3<T> up_norm = normalized(up);
  Vec3<T> left = cross(forward, up_norm);
  Vec3<T> up_res = cross(left, forward);

  Mat4<T> orientation;
  orientation.set(0, 0, left.x);
  orientation.set(0, 1, left.y);
  orientation.set(0, 2, left.z);
  orientation.set(0, 3, T{0});
  orientation.set(1, 0, up_res.x);
  orientation.set(1, 1, up_res.y);
  orientation.set(1, 2, up_res.z);
  orientation.set(1, 3, T{0});
  orientation.set(2, 0, -forward.x);
  orientation.set(2, 1, -forward.y);
  orientation.set(2, 2, -forward.z);
  orientation.set(2, 3, T{0});
  orientation.set(3, 0, T{0});
  orientation.set(3, 1, T{0});
  orientation.set(3, 2, T{0});
  orientation.set(3, 3, T{1});

  return orientation * translation(-from.x, -from.y, -from.z);
}

// TODO: Shearing

template <numeric T>
std::ostream& operator<<(std::ostream& out, const Mat4<T>& m) {
  out << "{" << m[0] << "," << m[1] << "," << m[2] << "," << m[3] << "}";
  return out;
}

constexpr inline Mat4f frustrum(float left, float right, float bottom,
                                float top, float near, float far) {
  if (left == right || top == bottom || near == far) {
    assert(false);
    return Mat4f();
  }
  Mat4f ret;
  ret.set(0, 0, (2.f * near) / (right - left));
  ret.set(1, 1, (2.f * near) / (top - bottom));
  ret.set(0, 2, (right + left) / (right - left));
  ret.set(1, 2, (top + bottom) / (top - bottom));
  ret.set(2, 2, -(far + near) / (far - near));
  ret.set(3, 2, -1.f);
  ret.set(2, 3, (-2.f * far * near) / (far - near));
  return ret;
}

constexpr inline Mat4f perspective(float fov, float aspect, float n, float f) {
  auto ymax = n * tanf(fov * PI / RAD);
  auto xmax = ymax * aspect;
  return frustrum(-xmax, xmax, -ymax, ymax, n, f);
}

constexpr inline Mat4f orthographic(float left, float right, float bottom,
                                    float top, float near, float far) {
  Mat4f ret;
  ret.set(0, 0, 2.f / (right - left));
  ret.set(1, 1, 2.f / (top - bottom));
  ret.set(2, 2, -2.f / (far - near));
  ret.set(3, 3, 1.f);
  ret.set(0, 3, -(right + left) / (right - left));
  ret.set(1, 3, -(top + bottom) / (top - bottom));
  ret.set(2, 3, -(far + near) / (far - near));
  return ret;
}

template <typename T>
constexpr Mat4<T> LookAt(const Vec3<T>& pos, const Vec3<T>& target,
                         const Vec3<T>& up) {
  Vec3<T> fwd = normalized(target - pos) * -T{1};
  Vec3<T> right = cross(up, fwd);
  if (right == Vec3<T>(T{0}, T{0}, T{0})) {
    return Mat4<T>();  // Error
  }
  right.normalize();
  auto up_norm = normalized(cross(fwd, right));

  auto t = Vec3<T>(-dot(right, pos), -dot(up_norm, pos), -dot(fwd, pos));

  Mat4<T> ret;
  ret.set(0, 0, right.x);
  ret.set(0, 1, up_norm.x);
  ret.set(0, 2, fwd.x);
  ret.set(0, 3, T{0});
  ret.set(1, 0, right.y);
  ret.set(1, 1, up_norm.y);
  ret.set(1, 2, fwd.y);
  ret.set(1, 3, T{0});
  ret.set(2, 0, right.z);
  ret.set(2, 1, up_norm.z);
  ret.set(2, 2, fwd.z);
  ret.set(2, 3, T{0});
  ret.set(3, 0, t.x);
  ret.set(3, 1, t.y);
  ret.set(3, 2, t.z);
  ret.set(3, 3, T{1});
  return ret;
}