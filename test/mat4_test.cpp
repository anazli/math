#include "mat4.h"

#include "gtest/gtest.h"
#include "vec4.h"

class Matrix4Test : public testing::Test {
 public:
  Mat4<double> m4;
};

TEST_F(Matrix4Test, CreatesMatrix) {
  Vec4<double> v1(0., 0., 0., 0.);
  Vec4<double> v2(1., -1., 1., -1.);
  Vec4<double> v3(5., -9., 5., 9.);
  Vec4<double> v4(0., -1., 0., 0.);

  m4 = Mat4<double>(v1, v2, v3, v4);
  ASSERT_DOUBLE_EQ(m4[0][0], v1[0]);
  ASSERT_DOUBLE_EQ(m4[0][1], v1[1]);
  ASSERT_DOUBLE_EQ(m4[0][2], v1[2]);
  ASSERT_DOUBLE_EQ(m4[0][3], v1[3]);

  ASSERT_DOUBLE_EQ(m4[1][0], v2[0]);
  ASSERT_DOUBLE_EQ(m4[1][1], v2[1]);
  ASSERT_DOUBLE_EQ(m4[1][2], v2[2]);
  ASSERT_DOUBLE_EQ(m4[1][3], v2[3]);

  ASSERT_DOUBLE_EQ(m4[2][0], v3[0]);
  ASSERT_DOUBLE_EQ(m4[2][1], v3[1]);
  ASSERT_DOUBLE_EQ(m4[2][2], v3[2]);
  ASSERT_DOUBLE_EQ(m4[2][3], v3[3]);

  ASSERT_DOUBLE_EQ(m4[3][0], v4[0]);
  ASSERT_DOUBLE_EQ(m4[3][1], v4[1]);
  ASSERT_DOUBLE_EQ(m4[3][2], v4[2]);
  ASSERT_DOUBLE_EQ(m4[3][3], v4[3]);

  m4 = Mat4<double>(3.14);
  ASSERT_DOUBLE_EQ(m4[0][0], 3.14);
  ASSERT_DOUBLE_EQ(m4[0][1], 3.14);
  ASSERT_DOUBLE_EQ(m4[0][2], 3.14);
  ASSERT_DOUBLE_EQ(m4[0][3], 3.14);

  ASSERT_DOUBLE_EQ(m4[1][0], 3.14);
  ASSERT_DOUBLE_EQ(m4[1][1], 3.14);
  ASSERT_DOUBLE_EQ(m4[1][2], 3.14);
  ASSERT_DOUBLE_EQ(m4[1][3], 3.14);

  ASSERT_DOUBLE_EQ(m4[2][0], 3.14);
  ASSERT_DOUBLE_EQ(m4[2][1], 3.14);
  ASSERT_DOUBLE_EQ(m4[2][2], 3.14);
  ASSERT_DOUBLE_EQ(m4[2][3], 3.14);

  ASSERT_DOUBLE_EQ(m4[3][0], 3.14);
  ASSERT_DOUBLE_EQ(m4[3][1], 3.14);
  ASSERT_DOUBLE_EQ(m4[3][2], 3.14);
  ASSERT_DOUBLE_EQ(m4[3][3], 3.14);
}

TEST_F(Matrix4Test, AddsAmatrixOrNumber) {
  m4 = Mat4<double>(0.);
  m4 = m4 + Mat4<double>(-1.);
  ASSERT_DOUBLE_EQ(m4[0][0], -1.);
  ASSERT_DOUBLE_EQ(m4[0][1], -1.);
  ASSERT_DOUBLE_EQ(m4[0][2], -1.);
  ASSERT_DOUBLE_EQ(m4[0][3], -1.);

  ASSERT_DOUBLE_EQ(m4[1][0], -1.);
  ASSERT_DOUBLE_EQ(m4[1][1], -1.);
  ASSERT_DOUBLE_EQ(m4[1][2], -1.);
  ASSERT_DOUBLE_EQ(m4[1][3], -1.);

  ASSERT_DOUBLE_EQ(m4[2][0], -1.);
  ASSERT_DOUBLE_EQ(m4[2][1], -1.);
  ASSERT_DOUBLE_EQ(m4[2][2], -1.);
  ASSERT_DOUBLE_EQ(m4[2][3], -1.);

  ASSERT_DOUBLE_EQ(m4[3][0], -1.);
  ASSERT_DOUBLE_EQ(m4[3][1], -1.);
  ASSERT_DOUBLE_EQ(m4[3][2], -1.);
  ASSERT_DOUBLE_EQ(m4[3][3], -1.);
  m4 = m4 + 5.05;
  ASSERT_DOUBLE_EQ(m4[0][0], 4.05);
  ASSERT_DOUBLE_EQ(m4[0][1], 4.05);
  ASSERT_DOUBLE_EQ(m4[0][2], 4.05);
  ASSERT_DOUBLE_EQ(m4[0][3], 4.05);

  ASSERT_DOUBLE_EQ(m4[1][0], 4.05);
  ASSERT_DOUBLE_EQ(m4[1][1], 4.05);
  ASSERT_DOUBLE_EQ(m4[1][2], 4.05);
  ASSERT_DOUBLE_EQ(m4[1][3], 4.05);

  ASSERT_DOUBLE_EQ(m4[2][0], 4.05);
  ASSERT_DOUBLE_EQ(m4[2][1], 4.05);
  ASSERT_DOUBLE_EQ(m4[2][2], 4.05);
  ASSERT_DOUBLE_EQ(m4[2][3], 4.05);

  ASSERT_DOUBLE_EQ(m4[3][0], 4.05);
  ASSERT_DOUBLE_EQ(m4[3][1], 4.05);
  ASSERT_DOUBLE_EQ(m4[3][2], 4.05);
  ASSERT_DOUBLE_EQ(m4[3][3], 4.05);
}

TEST_F(Matrix4Test, SubtractsAmatrixOrNumber) {
  m4 = Mat4<double>(0.);
  m4 = m4 - Mat4<double>(1.);
  ASSERT_DOUBLE_EQ(m4[0][0], -1.);
  ASSERT_DOUBLE_EQ(m4[0][1], -1.);
  ASSERT_DOUBLE_EQ(m4[0][2], -1.);
  ASSERT_DOUBLE_EQ(m4[0][3], -1.);

  ASSERT_DOUBLE_EQ(m4[1][0], -1.);
  ASSERT_DOUBLE_EQ(m4[1][1], -1.);
  ASSERT_DOUBLE_EQ(m4[1][2], -1.);
  ASSERT_DOUBLE_EQ(m4[1][3], -1.);

  ASSERT_DOUBLE_EQ(m4[2][0], -1.);
  ASSERT_DOUBLE_EQ(m4[2][1], -1.);
  ASSERT_DOUBLE_EQ(m4[2][2], -1.);
  ASSERT_DOUBLE_EQ(m4[2][3], -1.);

  ASSERT_DOUBLE_EQ(m4[3][0], -1.);
  ASSERT_DOUBLE_EQ(m4[3][1], -1.);
  ASSERT_DOUBLE_EQ(m4[3][2], -1.);
  ASSERT_DOUBLE_EQ(m4[3][3], -1.);
  m4 = m4 - 5.05;
  ASSERT_DOUBLE_EQ(m4[0][0], -6.05);
  ASSERT_DOUBLE_EQ(m4[0][1], -6.05);
  ASSERT_DOUBLE_EQ(m4[0][2], -6.05);
  ASSERT_DOUBLE_EQ(m4[0][3], -6.05);

  ASSERT_DOUBLE_EQ(m4[1][0], -6.05);
  ASSERT_DOUBLE_EQ(m4[1][1], -6.05);
  ASSERT_DOUBLE_EQ(m4[1][2], -6.05);
  ASSERT_DOUBLE_EQ(m4[1][3], -6.05);

  ASSERT_DOUBLE_EQ(m4[2][0], -6.05);
  ASSERT_DOUBLE_EQ(m4[2][1], -6.05);
  ASSERT_DOUBLE_EQ(m4[2][2], -6.05);
  ASSERT_DOUBLE_EQ(m4[2][3], -6.05);

  ASSERT_DOUBLE_EQ(m4[3][0], -6.05);
  ASSERT_DOUBLE_EQ(m4[3][1], -6.05);
  ASSERT_DOUBLE_EQ(m4[3][2], -6.05);
  ASSERT_DOUBLE_EQ(m4[3][3], -6.05);
}

TEST_F(Matrix4Test, MultipliesWithNumber) {
  m4 = Mat4<double>(6.28);
  m4 = m4 * 0.;
  ASSERT_DOUBLE_EQ(m4[0][0], 0.);
  ASSERT_DOUBLE_EQ(m4[0][1], 0.);
  ASSERT_DOUBLE_EQ(m4[0][2], 0.);
  ASSERT_DOUBLE_EQ(m4[0][3], 0.);

  ASSERT_DOUBLE_EQ(m4[1][0], 0.);
  ASSERT_DOUBLE_EQ(m4[1][1], 0.);
  ASSERT_DOUBLE_EQ(m4[1][2], 0.);
  ASSERT_DOUBLE_EQ(m4[1][3], 0.);

  ASSERT_DOUBLE_EQ(m4[2][0], 0.);
  ASSERT_DOUBLE_EQ(m4[2][1], 0.);
  ASSERT_DOUBLE_EQ(m4[2][2], 0.);
  ASSERT_DOUBLE_EQ(m4[2][3], 0.);

  ASSERT_DOUBLE_EQ(m4[3][0], 0.);
  ASSERT_DOUBLE_EQ(m4[3][1], 0.);
  ASSERT_DOUBLE_EQ(m4[3][2], 0.);
  ASSERT_DOUBLE_EQ(m4[3][3], 0.);
}

TEST_F(Matrix4Test, GetsTheDeterminant) {
  m4 = Mat4<double>(
      Vec4<double>(5.36, 2.28, 0.93, 13.), Vec4<double>(-1.5, 85., 0., 5.),
      Vec4<double>(45.8, -50., 0.14, -1.5), Vec4<double>(0.48, -38.5, 0., -1.));
  ASSERT_DOUBLE_EQ(m4.determinant(), -4401.55547);

  Mat4<float> m4f = Mat4<float>(
      Vec4<float>(-2.f, -8.f, 3.f, 5.f), Vec4<float>(-3.f, 1.f, 7.f, 3.f),
      Vec4<float>(1.f, 2.f, -9.f, 6.f), Vec4<float>(-6.f, 7.f, 7.f, -9.f));
  ASSERT_DOUBLE_EQ(m4f.determinant(), -4071.f);
}

TEST_F(Matrix4Test, AddsTwoMatrices) {
  m4 = Mat4<double>(
      Vec4<double>(1.36, 1.28, 1., 0.), Vec4<double>(1.5, 0., -1., -2.),
      Vec4<double>(6.3, 0.5, 0.8, -6.), Vec4<double>(0.5, 3.38, -2., 5.));

  m4 = m4 + Mat4<double>(Vec4<double>(9., -5.8, 0., 0.),
                         Vec4<double>(-6.5, 5.3, -1.5, -2.5),
                         Vec4<double>(-5., 0.4, 90., 3.5),
                         Vec4<double>(5., 0.4, 0.5, 3.5));

  ASSERT_DOUBLE_EQ(m4[0][0], 10.36);
  ASSERT_DOUBLE_EQ(m4[0][1], -4.52);
  ASSERT_DOUBLE_EQ(m4[0][2], 1.);
  ASSERT_DOUBLE_EQ(m4[0][3], 0.);

  ASSERT_DOUBLE_EQ(m4[1][0], -5.);
  ASSERT_DOUBLE_EQ(m4[1][1], 5.3);
  ASSERT_DOUBLE_EQ(m4[1][2], -2.5);
  ASSERT_DOUBLE_EQ(m4[1][3], -4.5);

  ASSERT_DOUBLE_EQ(m4[2][0], 1.3);
  ASSERT_DOUBLE_EQ(m4[2][1], 0.9);
  ASSERT_DOUBLE_EQ(m4[2][2], 90.8);
  ASSERT_DOUBLE_EQ(m4[2][3], -2.5);

  ASSERT_DOUBLE_EQ(m4[3][0], 5.5);
  ASSERT_DOUBLE_EQ(m4[3][1], 3.78);
  ASSERT_DOUBLE_EQ(m4[3][2], -1.5);
  ASSERT_DOUBLE_EQ(m4[3][3], 8.5);
}

TEST_F(Matrix4Test, MultipliesTwoMatrices) {
  m4 = Mat4<double>(
      Vec4<double>(1.36, 1.28, 0.85, -1.), Vec4<double>(1.5, 0., -6.58, 0.),
      Vec4<double>(4.5, 0., -3., 0.), Vec4<double>(5.8, -3.4, 0., -1));
  Mat4<double> m2(
      Vec4<double>(9., -5.8, -4.5, -1.1), Vec4<double>(-6.5, 5.3, 20., 2.2),
      Vec4<double>(8.6, 33., -5., -4.),
      Vec4<double>(0., -5., 8.,
                   -3.));  // With an anonymous object, it doesn't pass
  m4 = m4 * m2;

  ASSERT_DOUBLE_EQ(m4[0][0], 11.23);
  ASSERT_DOUBLE_EQ(m4[0][1], 31.946);
  ASSERT_DOUBLE_EQ(m4[0][2], 7.23);
  ASSERT_DOUBLE_EQ(m4[0][3], 0.92);

  ASSERT_DOUBLE_EQ(m4[1][0], -43.088);
  ASSERT_DOUBLE_EQ(m4[1][1], -225.84);
  ASSERT_DOUBLE_EQ(m4[1][2], 26.15);
  ASSERT_DOUBLE_EQ(m4[1][3], 24.67);

  ASSERT_DOUBLE_EQ(m4[2][0], 14.7);
  ASSERT_DOUBLE_EQ(m4[2][1], -125.1);
  ASSERT_DOUBLE_EQ(m4[2][2], -5.25);
  ASSERT_DOUBLE_EQ(m4[2][3], 7.05);

  ASSERT_DOUBLE_EQ(m4[3][0], 74.3);
  ASSERT_DOUBLE_EQ(m4[3][1], -46.66);
  ASSERT_DOUBLE_EQ(m4[3][2], -102.1);
  ASSERT_DOUBLE_EQ(m4[3][3], -10.86);
}

TEST_F(Matrix4Test, GetTransposeOfMatrix) {
  m4 = Mat4<double>(
      Vec4<double>(1.36, 1.28, 0.85, -1.), Vec4<double>(1.5, 0., -6.58, -5.),
      Vec4<double>(4.5, 0., -3., 0.), Vec4<double>(3., 4., 5., 6.));

  Mat4<double> mt = m4.transpose();
  ASSERT_DOUBLE_EQ(mt[0][0], 1.36);
  ASSERT_DOUBLE_EQ(mt[0][1], 1.5);
  ASSERT_DOUBLE_EQ(mt[0][2], 4.5);
  ASSERT_DOUBLE_EQ(mt[0][3], 3.);

  ASSERT_DOUBLE_EQ(mt[1][0], 1.28);
  ASSERT_DOUBLE_EQ(mt[1][1], 0.);
  ASSERT_DOUBLE_EQ(mt[1][2], 0.);
  ASSERT_DOUBLE_EQ(mt[1][3], 4.);

  ASSERT_DOUBLE_EQ(mt[2][0], 0.85);
  ASSERT_DOUBLE_EQ(mt[2][1], -6.58);
  ASSERT_DOUBLE_EQ(mt[2][2], -3.);
  ASSERT_DOUBLE_EQ(mt[2][3], 5.);

  ASSERT_DOUBLE_EQ(mt[3][0], -1.);
  ASSERT_DOUBLE_EQ(mt[3][1], -5.);
  ASSERT_DOUBLE_EQ(mt[3][2], 0.);
  ASSERT_DOUBLE_EQ(mt[3][3], 6.);
}

TEST_F(Matrix4Test, GetInverseOfMatrix) {
  m4 = Mat4<double>(
      Vec4<double>(1.36, 1.28, 0.85, -7.), Vec4<double>(1.5, 0., -6.58, 1.),
      Vec4<double>(4.5, 0., -3., 10.), Vec4<double>(0., 1., 6.68, -9.));

  m4 = m4.inverse();

  ASSERT_DOUBLE_EQ(m4[0][0], -0.57644611789241018751);
  ASSERT_DOUBLE_EQ(m4[0][1], 0.58235744432430050861);
  ASSERT_DOUBLE_EQ(m4[0][2], 0.20231790085493935382);
  ASSERT_DOUBLE_EQ(m4[0][3], 0.73785103090228503992);

  ASSERT_DOUBLE_EQ(m4[1][0], 2.7182004600554049173);
  ASSERT_DOUBLE_EQ(m4[1][1], -2.1123170380215781781);
  ASSERT_DOUBLE_EQ(m4[1][2], -0.1173949041428852046);
  ASSERT_DOUBLE_EQ(m4[1][3], -2.4792965888709182942);

  ASSERT_DOUBLE_EQ(m4[2][0], -0.096380322259081321122);
  ASSERT_DOUBLE_EQ(m4[2][1], -0.06186698781201981947);
  ASSERT_DOUBLE_EQ(m4[2][2], 0.049750604442306739096);
  ASSERT_DOUBLE_EQ(m4[2][3], 0.12336681249162409103);

  ASSERT_DOUBLE_EQ(m4[3][0], 0.23048665637386018803);
  ASSERT_DOUBLE_EQ(m4[3][1], -0.28062094628954117469);
  ASSERT_DOUBLE_EQ(m4[3][2], 0.023882125947969312508);
  ASSERT_DOUBLE_EQ(m4[3][3], -0.29502292015854104069);

  Mat4<float> m4f = Mat4<float>(
      Vec4<float>(-5.f, 2.f, 6.f, -8.f), Vec4<float>(1.f, -5.f, 1.f, 8.f),
      Vec4<float>(7.f, 7.f, -6.f, -7.f), Vec4<float>(1.f, -3.f, 7.f, 4.f));

  m4f = m4f.inverse();

  float eps{10E-5f};

  EXPECT_NEAR(m4f[0][0], 0.218045f, eps);
  EXPECT_NEAR(m4f[0][1], 0.45113f, eps);
  EXPECT_NEAR(m4f[0][2], 0.24060f, eps);
  EXPECT_NEAR(m4f[0][3], -0.04511f, eps);

  EXPECT_NEAR(m4f[1][0], -0.80827f, eps);
  EXPECT_NEAR(m4f[1][1], -1.456777f, eps);
  EXPECT_NEAR(m4f[1][2], -0.44361f, eps);
  EXPECT_NEAR(m4f[1][3], 0.52068f, eps);

  EXPECT_NEAR(m4f[2][0], -0.07895f, eps);
  EXPECT_NEAR(m4f[2][1], -0.22368f, eps);
  EXPECT_NEAR(m4f[2][2], -0.05263f, eps);
  EXPECT_NEAR(m4f[2][3], 0.19737f, eps);

  EXPECT_NEAR(m4f[3][0], -0.52256f, eps);
  EXPECT_NEAR(m4f[3][1], -0.81391f, eps);
  EXPECT_NEAR(m4f[3][2], -0.30075f, eps);
  EXPECT_NEAR(m4f[3][3], 0.30639f, eps);
}