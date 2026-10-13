#include "mat3.h"

#include "gtest/gtest.h"
#include "vec3.h"

class Matrix3Test : public testing::Test {
 public:
  Mat3<double> m;
};

TEST_F(Matrix3Test, CreatesMatrix) {
  constexpr Vec3<double> v1(0., 0., 0.);
  constexpr Vec3<double> v2(1., -1., 1.);
  constexpr Vec3<double> v3(5., -9., 5.);

  constexpr auto m1 = Mat3<double>(v1, v2, v3);
  ASSERT_DOUBLE_EQ(m1[0][0], v1[0]);
  ASSERT_DOUBLE_EQ(m1[0][1], v1[1]);
  ASSERT_DOUBLE_EQ(m1[0][2], v1[2]);

  ASSERT_DOUBLE_EQ(m1[1][0], v2[0]);
  ASSERT_DOUBLE_EQ(m1[1][1], v2[1]);
  ASSERT_DOUBLE_EQ(m1[1][2], v2[2]);

  ASSERT_DOUBLE_EQ(m1[2][0], v3[0]);
  ASSERT_DOUBLE_EQ(m1[2][1], v3[1]);
  ASSERT_DOUBLE_EQ(m1[2][2], v3[2]);

  constexpr auto m2 = Mat3<double>(3.14);
  ASSERT_DOUBLE_EQ(m2[0][0], 3.14);
  ASSERT_DOUBLE_EQ(m2[0][1], 3.14);
  ASSERT_DOUBLE_EQ(m2[0][2], 3.14);

  ASSERT_DOUBLE_EQ(m2[1][0], 3.14);
  ASSERT_DOUBLE_EQ(m2[1][1], 3.14);
  ASSERT_DOUBLE_EQ(m2[1][2], 3.14);

  ASSERT_DOUBLE_EQ(m2[2][0], 3.14);
  ASSERT_DOUBLE_EQ(m2[2][1], 3.14);
  ASSERT_DOUBLE_EQ(m2[2][2], 3.14);
}

TEST_F(Matrix3Test, AddsAmatrixOrNumber) {
  constexpr auto m1 = Mat3<double>(0.);
  constexpr auto m2 = m1 + Mat3<double>(-1.);
  constexpr auto m3 = m2 + 5.05;
  ASSERT_DOUBLE_EQ(m2[0][0], -1.);
  ASSERT_DOUBLE_EQ(m2[0][1], -1.);
  ASSERT_DOUBLE_EQ(m2[0][2], -1.);

  ASSERT_DOUBLE_EQ(m2[1][0], -1.);
  ASSERT_DOUBLE_EQ(m2[1][1], -1.);
  ASSERT_DOUBLE_EQ(m2[1][2], -1.);

  ASSERT_DOUBLE_EQ(m2[2][0], -1.);
  ASSERT_DOUBLE_EQ(m2[2][1], -1.);
  ASSERT_DOUBLE_EQ(m2[2][2], -1.);
  ASSERT_DOUBLE_EQ(m3[0][0], 4.05);
  ASSERT_DOUBLE_EQ(m3[0][1], 4.05);
  ASSERT_DOUBLE_EQ(m3[0][2], 4.05);

  ASSERT_DOUBLE_EQ(m3[1][0], 4.05);
  ASSERT_DOUBLE_EQ(m3[1][1], 4.05);
  ASSERT_DOUBLE_EQ(m3[1][2], 4.05);

  ASSERT_DOUBLE_EQ(m3[2][0], 4.05);
  ASSERT_DOUBLE_EQ(m3[2][1], 4.05);
  ASSERT_DOUBLE_EQ(m3[2][2], 4.05);
}

TEST_F(Matrix3Test, SubtractsAmatrixOrNumber) {
  constexpr auto m1 = Mat3<double>(0.);
  constexpr auto m2 = m1 - Mat3<double>(1.);
  constexpr auto m3 = m2 - 5.05;
  ASSERT_DOUBLE_EQ(m2[0][0], -1.);
  ASSERT_DOUBLE_EQ(m2[0][1], -1.);
  ASSERT_DOUBLE_EQ(m2[0][2], -1.);
  ASSERT_DOUBLE_EQ(m2[1][0], -1.);
  ASSERT_DOUBLE_EQ(m2[1][1], -1.);
  ASSERT_DOUBLE_EQ(m2[1][2], -1.);
  ASSERT_DOUBLE_EQ(m2[2][0], -1.);
  ASSERT_DOUBLE_EQ(m2[2][1], -1.);
  ASSERT_DOUBLE_EQ(m2[2][2], -1.);
  ASSERT_DOUBLE_EQ(m3[0][0], -6.05);
  ASSERT_DOUBLE_EQ(m3[0][1], -6.05);
  ASSERT_DOUBLE_EQ(m3[0][2], -6.05);
  ASSERT_DOUBLE_EQ(m3[1][0], -6.05);
  ASSERT_DOUBLE_EQ(m3[1][1], -6.05);
  ASSERT_DOUBLE_EQ(m3[1][2], -6.05);
  ASSERT_DOUBLE_EQ(m3[2][0], -6.05);
  ASSERT_DOUBLE_EQ(m3[2][1], -6.05);
  ASSERT_DOUBLE_EQ(m3[2][2], -6.05);
}

TEST_F(Matrix3Test, MultipliesWithNumber) {
  constexpr auto m1 = Mat3<double>(6.28);
  constexpr auto m2 = m1 * 0.;
  ASSERT_DOUBLE_EQ(m2[0][0], 0.);
  ASSERT_DOUBLE_EQ(m2[0][1], 0.);
  ASSERT_DOUBLE_EQ(m2[0][2], 0.);
  ASSERT_DOUBLE_EQ(m2[1][0], 0.);
  ASSERT_DOUBLE_EQ(m2[1][1], 0.);
  ASSERT_DOUBLE_EQ(m2[1][2], 0.);
  ASSERT_DOUBLE_EQ(m2[2][0], 0.);
  ASSERT_DOUBLE_EQ(m2[2][1], 0.);
  ASSERT_DOUBLE_EQ(m2[2][2], 0.);
}

TEST_F(Matrix3Test, GetsTheDeterminant) {
  constexpr auto m1 =
      Mat3<double>(Vec3<double>(5.36, 2.28, 0.93), Vec3<double>(-1.5, 85., 0.),
                   Vec3<double>(45.8, -50., 0.14));
  ASSERT_DOUBLE_EQ(m1.determinant(), -3486.4772);
}

TEST_F(Matrix3Test, AddsTwoMatrices) {
  constexpr auto m1 =
      Mat3<double>(Vec3<double>(1.36, 1.28, 1.), Vec3<double>(1.5, 0., -1.),
                   Vec3<double>(6.3, 0.5, 0.8));
  constexpr auto m2 = m1 + Mat3<double>(Vec3<double>(9., -5.8, 0.),
                                        Vec3<double>(-6.5, 5.3, -1.5),
                                        Vec3<double>(-5., 0.4, 90.));
  ASSERT_DOUBLE_EQ(m2[0][0], 10.36);
  ASSERT_DOUBLE_EQ(m2[0][1], -4.52);
  ASSERT_DOUBLE_EQ(m2[0][2], 1.);

  ASSERT_DOUBLE_EQ(m2[1][0], -5.);
  ASSERT_DOUBLE_EQ(m2[1][1], 5.3);
  ASSERT_DOUBLE_EQ(m2[1][2], -2.5);

  ASSERT_DOUBLE_EQ(m2[2][0], 1.3);
  ASSERT_DOUBLE_EQ(m2[2][1], 0.9);
  ASSERT_DOUBLE_EQ(m2[2][2], 90.8);
}

TEST_F(Matrix3Test, MultipliesTwoMatrices) {
  constexpr auto m1 =
      Mat3<double>(Vec3<double>(1.36, 1.28, 0.85), Vec3<double>(1.5, 0., -6.58),
                   Vec3<double>(4.5, 0., -3.));
  constexpr Mat3<double> m2(
      Vec3<double>(9., -5.8, -4.5), Vec3<double>(-6.5, 5.3, 20.),
      Vec3<double>(8.6, 33.,
                   -5.));  // With an anonymous object, it doesn't pass
  constexpr auto m3 = m1 * m2;

  ASSERT_DOUBLE_EQ(m3[0][0], 11.23);
  ASSERT_DOUBLE_EQ(m3[0][1], 26.946);
  ASSERT_DOUBLE_EQ(m3[0][2], 15.23);

  ASSERT_DOUBLE_EQ(m3[1][0], -43.088);
  ASSERT_DOUBLE_EQ(m3[1][1], -225.84);
  ASSERT_DOUBLE_EQ(m3[1][2], 26.15);

  ASSERT_DOUBLE_EQ(m3[2][0], 14.7);
  ASSERT_DOUBLE_EQ(m3[2][1], -125.1);
  ASSERT_DOUBLE_EQ(m3[2][2], -5.25);
}

TEST_F(Matrix3Test, GetTransposeOfMatrix) {
  constexpr auto m1 =
      Mat3<double>(Vec3<double>(1.36, 1.28, 0.85), Vec3<double>(1.5, 0., -6.58),
                   Vec3<double>(4.5, 0., -3.));

  constexpr auto mt = m1.transpose();
  ASSERT_DOUBLE_EQ(mt[0][0], 1.36);
  ASSERT_DOUBLE_EQ(mt[0][1], 1.5);
  ASSERT_DOUBLE_EQ(mt[0][2], 4.5);

  ASSERT_DOUBLE_EQ(mt[1][0], 1.28);
  ASSERT_DOUBLE_EQ(mt[1][1], 0.);
  ASSERT_DOUBLE_EQ(mt[1][2], 0.);

  ASSERT_DOUBLE_EQ(mt[2][0], 0.85);
  ASSERT_DOUBLE_EQ(mt[2][1], -6.58);
  ASSERT_DOUBLE_EQ(mt[2][2], -3.);
}

TEST_F(Matrix3Test, GetInverseOfMatrix) {
  constexpr auto m1 =
      Mat3<double>(Vec3<double>(1.36, 1.28, 0.85), Vec3<double>(1.5, 0., -6.58),
                   Vec3<double>(4.5, 0., -3.));

  constexpr auto m2 = m1.inverse();

  ASSERT_DOUBLE_EQ(m2[0][0], 0.);
  ASSERT_DOUBLE_EQ(m2[0][1], -0.11947431302270011946);
  ASSERT_DOUBLE_EQ(m2[0][2], 0.26204699322978892872);

  ASSERT_DOUBLE_EQ(m2[1][0], 0.78125);
  ASSERT_DOUBLE_EQ(m2[1][1], 0.24594907407407407407);
  ASSERT_DOUBLE_EQ(m2[1][2], -0.31809413580246913581);

  ASSERT_DOUBLE_EQ(m2[2][0], 0.);
  ASSERT_DOUBLE_EQ(m2[2][1], -0.17921146953405017921);
  ASSERT_DOUBLE_EQ(m2[2][2], 0.059737156511350059737);
}