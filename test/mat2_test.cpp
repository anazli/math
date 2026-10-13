#include "mat2.h"

#include "gtest/gtest.h"
#include "vec2.h"

class Matrix2Test : public testing::Test {
 public:
  Mat2<double> m;
};

TEST_F(Matrix2Test, CreatesMatrix) {
  constexpr Vec2<double> v1(0., 0.);
  constexpr Vec2<double> v2(1., -1.);

  constexpr auto m1 = Mat2<double>(v1, v2);
  ASSERT_DOUBLE_EQ(m1[0].x, v1.x);
  ASSERT_DOUBLE_EQ(m1[0].y, v1.y);
  ASSERT_DOUBLE_EQ(m1[1].x, v2.x);
  ASSERT_DOUBLE_EQ(m1[1].y, v2.y);

  constexpr auto m2 = Mat2<double>(3.14);
  ASSERT_DOUBLE_EQ(m2[0].x, 3.14);
  ASSERT_DOUBLE_EQ(m2[0].y, 3.14);
  ASSERT_DOUBLE_EQ(m2[1].x, 3.14);
  ASSERT_DOUBLE_EQ(m2[1].y, 3.14);
}

TEST_F(Matrix2Test, AddsAmatrixOrNumber) {
  constexpr auto m1 = Mat2<double>(0.);
  constexpr auto m2 = m1 + Mat2<double>(-1.);
  constexpr auto m3 = m2 + 5.05;
  ASSERT_DOUBLE_EQ(m2[0].x, -1.);
  ASSERT_DOUBLE_EQ(m2[0].y, -1.);
  ASSERT_DOUBLE_EQ(m2[1].x, -1.);
  ASSERT_DOUBLE_EQ(m2[1].y, -1.);
  ASSERT_DOUBLE_EQ(m3[0].x, 4.05);
  ASSERT_DOUBLE_EQ(m3[0].y, 4.05);
  ASSERT_DOUBLE_EQ(m3[1].x, 4.05);
  ASSERT_DOUBLE_EQ(m3[1].y, 4.05);
}

TEST_F(Matrix2Test, SubtractsAmatrixOrNumber) {
  constexpr auto m1 = Mat2<double>(0.);
  constexpr auto m2 = m1 - Mat2<double>(1.);
  constexpr auto m3 = m2 - 5.05;
  ASSERT_DOUBLE_EQ(m2[0].x, -1.);
  ASSERT_DOUBLE_EQ(m2[0].y, -1.);
  ASSERT_DOUBLE_EQ(m2[1].x, -1.);
  ASSERT_DOUBLE_EQ(m2[1].y, -1.);
  ASSERT_DOUBLE_EQ(m3[0].x, -6.05);
  ASSERT_DOUBLE_EQ(m3[0].y, -6.05);
  ASSERT_DOUBLE_EQ(m3[1].x, -6.05);
  ASSERT_DOUBLE_EQ(m3[1].y, -6.05);
}

TEST_F(Matrix2Test, MultipliesWithNumber) {
  constexpr auto m1 = Mat2<double>(6.28);
  constexpr auto m2 = m1 * 0.;
  ASSERT_DOUBLE_EQ(m2[0].x, 0.);
  ASSERT_DOUBLE_EQ(m2[0].y, 0.);
  ASSERT_DOUBLE_EQ(m2[1].x, 0.);
  ASSERT_DOUBLE_EQ(m2[1].y, 0.);
}

TEST_F(Matrix2Test, GetsTheDeterminant) {
  constexpr auto m1 =
      Mat2<double>(Vec2<double>(5.36, 2.28), Vec2<double>(-1.5, 85.));
  ASSERT_DOUBLE_EQ(m1.determinant(), 459.02);
}

TEST_F(Matrix2Test, AddsTwoMatrices) {
  constexpr auto m1 =
      Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  constexpr auto m2 =
      m1 + Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m2[0].x, 10.36);
  ASSERT_DOUBLE_EQ(m2[0].y, -4.52);
  ASSERT_DOUBLE_EQ(m2[1].x, -5.);
  ASSERT_DOUBLE_EQ(m2[1].y, 5.3);
}

TEST_F(Matrix2Test, MultipliesTwoMatrices) {
  constexpr auto m1 =
      Mat2<double>(Vec2<double>(1.36, 1.28), Vec2<double>(1.5, 0.));
  constexpr auto m2 =
      m1 * Mat2<double>(Vec2<double>(9., -5.8), Vec2<double>(-6.5, 5.3));
  ASSERT_DOUBLE_EQ(m2[0].x, 3.92);
  ASSERT_DOUBLE_EQ(m2[0].y, -1.104);
  ASSERT_DOUBLE_EQ(m2[1].x, 13.5);
  ASSERT_DOUBLE_EQ(m2[1].y, -8.7);
}