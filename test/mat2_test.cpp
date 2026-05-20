#include "mat2.h"

#include "gtest/gtest.h"
#include "vec2.h"

class Matrix2Test : public testing::Test {
 public:
  Mat2<double> m;
};

TEST_F(Matrix2Test, CreatesMatrix) {
  Vec2<double> v1(0., 0.);
  Vec2<double> v2(1., -1.);

  m = Mat2<double>(v1, v2);
  ASSERT_DOUBLE_EQ(m[0].x, v1.x);
  ASSERT_DOUBLE_EQ(m[0].y, v1.y);
  ASSERT_DOUBLE_EQ(m[1].x, v2.x);
  ASSERT_DOUBLE_EQ(m[1].y, v2.y);

  m = Mat2<double>(3.14);
  ASSERT_DOUBLE_EQ(m[0].x, 3.14);
  ASSERT_DOUBLE_EQ(m[0].y, 3.14);
  ASSERT_DOUBLE_EQ(m[1].x, 3.14);
  ASSERT_DOUBLE_EQ(m[1].y, 3.14);
}

TEST_F(Matrix2Test, AddsAmatrixOrNumber) {
  m = Mat2<double>(0.);
  m = m + Mat2<double>(-1.);
  ASSERT_DOUBLE_EQ(m[0].x, -1.);
  ASSERT_DOUBLE_EQ(m[0].y, -1.);
  ASSERT_DOUBLE_EQ(m[1].x, -1.);
  ASSERT_DOUBLE_EQ(m[1].y, -1.);
  m = m + 5.05;
  ASSERT_DOUBLE_EQ(m[0].x, 4.05);
  ASSERT_DOUBLE_EQ(m[0].y, 4.05);
  ASSERT_DOUBLE_EQ(m[1].x, 4.05);
  ASSERT_DOUBLE_EQ(m[1].y, 4.05);
}

TEST_F(Matrix2Test, SubtractsAmatrixOrNumber) {
  m = Mat2<double>(0.);
  m = m - Mat2<double>(1.);
  ASSERT_DOUBLE_EQ(m[0].x, -1.);
  ASSERT_DOUBLE_EQ(m[0].y, -1.);
  ASSERT_DOUBLE_EQ(m[1].x, -1.);
  ASSERT_DOUBLE_EQ(m[1].y, -1.);
  m = m - 5.05;
  ASSERT_DOUBLE_EQ(m[0].x, -6.05);
  ASSERT_DOUBLE_EQ(m[0].y, -6.05);
  ASSERT_DOUBLE_EQ(m[1].x, -6.05);
  ASSERT_DOUBLE_EQ(m[1].y, -6.05);
}

TEST_F(Matrix2Test, MultipliesWithNumber) {
  m = Mat2<double>(6.28);
  m = m * 0.;
  ASSERT_DOUBLE_EQ(m[0].x, 0.);
  ASSERT_DOUBLE_EQ(m[0].y, 0.);
  ASSERT_DOUBLE_EQ(m[1].x, 0.);
  ASSERT_DOUBLE_EQ(m[1].y, 0.);
}

TEST_F(Matrix2Test, GetsTheDeterminant) {
  m = Mat2<double>(Vec2<double>(5.36, 2.28), Vec2<double>(-1.5, 85.));
  ASSERT_DOUBLE_EQ(m.determinant(), 459.02);
}

TEST_F(Matrix2Test, AddsTwoMatrices) {
  m = Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  m = m + Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m[0].x, 10.36);
  ASSERT_DOUBLE_EQ(m[0].y, -4.52);
  ASSERT_DOUBLE_EQ(m[1].x, -5.);
  ASSERT_DOUBLE_EQ(m[1].y, 5.3);
}

TEST_F(Matrix2Test, MultipliesTwoMatrices) {
  m = Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  m = m * Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m[0].x, 3.92);
  ASSERT_DOUBLE_EQ(m[0].y, -1.104);
  ASSERT_DOUBLE_EQ(m[1].x, 13.5);
  ASSERT_DOUBLE_EQ(m[1].y, -8.7);
}