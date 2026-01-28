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
  ASSERT_DOUBLE_EQ(m[0][0], v1[0]);
  ASSERT_DOUBLE_EQ(m[0][1], v1[1]);
  ASSERT_DOUBLE_EQ(m[1][0], v2[0]);
  ASSERT_DOUBLE_EQ(m[1][1], v2[1]);

  m = Mat2<double>(3.14);
  ASSERT_DOUBLE_EQ(m[0][0], 3.14);
  ASSERT_DOUBLE_EQ(m[0][1], 3.14);
  ASSERT_DOUBLE_EQ(m[1][0], 3.14);
  ASSERT_DOUBLE_EQ(m[1][1], 3.14);
}

TEST_F(Matrix2Test, AddsAmatrixOrNumber) {
  m = Mat2<double>(0.);
  m = m + Mat2<double>(-1.);
  ASSERT_DOUBLE_EQ(m[0][0], -1.);
  ASSERT_DOUBLE_EQ(m[0][1], -1.);
  ASSERT_DOUBLE_EQ(m[1][0], -1.);
  ASSERT_DOUBLE_EQ(m[1][1], -1.);
  m = m + 5.05;
  ASSERT_DOUBLE_EQ(m[0][0], 4.05);
  ASSERT_DOUBLE_EQ(m[0][1], 4.05);
  ASSERT_DOUBLE_EQ(m[1][0], 4.05);
  ASSERT_DOUBLE_EQ(m[1][1], 4.05);
}

TEST_F(Matrix2Test, SubtractsAmatrixOrNumber) {
  m = Mat2<double>(0.);
  m = m - Mat2<double>(1.);
  ASSERT_DOUBLE_EQ(m[0][0], -1.);
  ASSERT_DOUBLE_EQ(m[0][1], -1.);
  ASSERT_DOUBLE_EQ(m[1][0], -1.);
  ASSERT_DOUBLE_EQ(m[1][1], -1.);
  m = m - 5.05;
  ASSERT_DOUBLE_EQ(m[0][0], -6.05);
  ASSERT_DOUBLE_EQ(m[0][1], -6.05);
  ASSERT_DOUBLE_EQ(m[1][0], -6.05);
  ASSERT_DOUBLE_EQ(m[1][1], -6.05);
}

TEST_F(Matrix2Test, MultipliesWithNumber) {
  m = Mat2<double>(6.28);
  m = m * 0.;
  ASSERT_DOUBLE_EQ(m[0][0], 0.);
  ASSERT_DOUBLE_EQ(m[0][1], 0.);
  ASSERT_DOUBLE_EQ(m[1][0], 0.);
  ASSERT_DOUBLE_EQ(m[1][1], 0.);
}

TEST_F(Matrix2Test, GetsTheDeterminant) {
  m = Mat2<double>(Vec2<double>(5.36, 2.28), Vec2<double>(-1.5, 85.));
  ASSERT_DOUBLE_EQ(m.determinant(), 459.02);
}

TEST_F(Matrix2Test, AddsTwoMatrices) {
  m = Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  m = m + Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m[0][0], 10.36);
  ASSERT_DOUBLE_EQ(m[0][1], -4.52);
  ASSERT_DOUBLE_EQ(m[1][0], -5.);
  ASSERT_DOUBLE_EQ(m[1][1], 5.3);
}

TEST_F(Matrix2Test, MultipliesTwoMatrices) {
  m = Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  m = m * Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m[0][0], 3.92);
  ASSERT_DOUBLE_EQ(m[0][1], -1.104);
  ASSERT_DOUBLE_EQ(m[1][0], 13.5);
  ASSERT_DOUBLE_EQ(m[1][1], -8.7);
}