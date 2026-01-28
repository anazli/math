#include "gtest/gtest.h"

class Vector4Test : public testing::Test {
 public:
  Vec4<double> v;
};

TEST_F(Vector4Test, CreatesVector) {
  v = Vec4<double>(0., 0., 0., 0.);
  ASSERT_DOUBLE_EQ(v.x(), 0.);
  ASSERT_DOUBLE_EQ(v.y(), 0.);
  ASSERT_DOUBLE_EQ(v.z(), 0.);
  ASSERT_DOUBLE_EQ(v.w(), 0.);
}

TEST_F(Vector4Test, AssertsOutOfBounds) {
  v = Vec4<double>(1., 2., 0.5, 7.5);
  ASSERT_DEATH(v[4], "");
  ASSERT_DEATH(v[-1], "");
}

TEST_F(Vector4Test, SetsCoords) {
  v.setX(5.);
  v[1] = 4.;
  v[2] = 0.2;
  v.setW(-5.2);
  ASSERT_DOUBLE_EQ(v.x(), 5.);
  ASSERT_DOUBLE_EQ(v[1], 4.);
  ASSERT_DOUBLE_EQ(v[2], 0.2);
  ASSERT_DOUBLE_EQ(v[3], -5.2);
}

TEST_F(Vector4Test, SetXYZ) {
  v.set(-1.24, -5.54, 45.6, -0.5);
  ASSERT_DOUBLE_EQ(v.x(), -1.24);
  ASSERT_DOUBLE_EQ(v.y(), -5.54);
  ASSERT_DOUBLE_EQ(v.z(), 45.6);
  ASSERT_DOUBLE_EQ(v.w(), -0.5);

  v.set(6.68);
  ASSERT_DOUBLE_EQ(v.x(), 6.68);
  ASSERT_DOUBLE_EQ(v.y(), 6.68);
  ASSERT_DOUBLE_EQ(v.z(), 6.68);
  ASSERT_DOUBLE_EQ(v.w(), 6.68);
}

TEST_F(Vector4Test, ChangesSign) {
  v.set(-1.55);
  v = -v;
  ASSERT_DOUBLE_EQ(v[0], 1.55);
  ASSERT_DOUBLE_EQ(v[1], 1.55);
  ASSERT_DOUBLE_EQ(v[2], 1.55);
  ASSERT_DOUBLE_EQ(v[3], 1.55);
}

TEST_F(Vector4Test, AddsVectorOrNumber) {
  v = Vec4<double>(0., 0., 5., 3.5);
  v = v + 4.46;
  ASSERT_DOUBLE_EQ(v.x(), 4.46);
  ASSERT_DOUBLE_EQ(v.y(), 4.46);
  ASSERT_DOUBLE_EQ(v.z(), 9.46);
  ASSERT_DOUBLE_EQ(v.w(), 7.96);

  v = v + Vec4<double>(4., 6., 0., 45.);
  ASSERT_DOUBLE_EQ(v.x(), 8.46);
  ASSERT_DOUBLE_EQ(v.y(), 10.46);
  ASSERT_DOUBLE_EQ(v.z(), 9.46);
  ASSERT_DOUBLE_EQ(v.w(), 52.96);
}

TEST_F(Vector4Test, SubtractsVectorOrNumber) {
  v = Vec4<double>(0., 0., 3., -5.5);
  v = v - 4.46;
  ASSERT_DOUBLE_EQ(v.x(), -4.46);
  ASSERT_DOUBLE_EQ(v.y(), -4.46);
  ASSERT_DOUBLE_EQ(v.z(), -1.46);
  ASSERT_DOUBLE_EQ(v.w(), -9.96);

  v = v - Vec4<double>(4., 6., 0., -1.2);
  ASSERT_DOUBLE_EQ(v.x(), -8.46);
  ASSERT_DOUBLE_EQ(v.y(), -10.46);
  ASSERT_DOUBLE_EQ(v.z(), -1.46);
  ASSERT_DOUBLE_EQ(v.w(), -8.76);
}

TEST_F(Vector4Test, GetsLenghtOfVector) {
  v = Vec4<double>(0., 0., 0., 0.);
  ASSERT_DOUBLE_EQ(v.length(), 0.);
  v = Vec4<double>(1., 1., 1., 1.);
  ASSERT_DOUBLE_EQ(v.length(), sqrt(4.));
  v = Vec4<double>(3., 3., 3., 3.);
  ASSERT_DOUBLE_EQ(v.length(), sqrt(36.));
  v = Vec4<double>(-5., -5., 5., 5.);
  ASSERT_DOUBLE_EQ(v.length(), sqrt(100.));
}

TEST_F(Vector4Test, MultipliesVectorWithNumber) {
  v = Vec4<double>(1., 0., 5., -9.);
  v = v * 5.;
  ASSERT_DOUBLE_EQ(v.x(), 5.);
  ASSERT_DOUBLE_EQ(v.y(), 0.);
  ASSERT_DOUBLE_EQ(v.z(), 25.);
  ASSERT_DOUBLE_EQ(v.w(), -45.);
}

TEST_F(Vector4Test, NormalizesVector) {
  v = Vec4<double>(4.53, 93.5, -56.3, -100.00001);
  v.normalize();
  ASSERT_DOUBLE_EQ(v.length(), 1.);
}

TEST_F(Vector4Test, DotProduct) {
  v = Vec4<double>(3., 3., 4., 1.);
  ASSERT_DOUBLE_EQ(dot(v, Vec4<double>(3., 3., 9., -10.)), 44.);
  v = Vec4<double>(-1., 5., 9., -3.);
  ASSERT_DOUBLE_EQ(dot(v, Vec4<double>(-3., 3., 6., 0.)), 72.);
}

TEST_F(Vector4Test, GetUnitVectorOf) {
  v = Vec4<double>(4.36, 7.62, 0.466, -30485.55555555);
  v = getUnitVectorOf(v);
  ASSERT_DOUBLE_EQ(v.length(), 1.);
}

TEST_F(Vector4Test, AddsTwoVectors) {
  v = Vec4<double>(4.532, 45.67, 0.83, -44.6);
  v = v + Vec4<double>(0.3456, 124.67, 1., 9.);
  ASSERT_DOUBLE_EQ(v.x(), 4.8776);
  ASSERT_DOUBLE_EQ(v.y(), 170.34);
  ASSERT_DOUBLE_EQ(v.z(), 1.83);
  ASSERT_DOUBLE_EQ(v.w(), -35.6);
}

TEST_F(Vector4Test, SubtractsTwoVectors) {
  v = Vec4<double>(40.54, 2.4, 0.62, 0.);
  v = v - Vec4<double>(4.20, -1.7, -1., -99.99999);
  ASSERT_DOUBLE_EQ(v[0], 36.34);
  ASSERT_DOUBLE_EQ(v[1], 4.1);
  ASSERT_DOUBLE_EQ(v[2], 1.62);
  ASSERT_DOUBLE_EQ(v[3], 99.99999);
}

TEST_F(Vector4Test, DevidesVectorByNumber) {
  v = Vec4<double>(36.6, -30.6, 120.2586, -0.5555555);
  v = v / 3.;
  ASSERT_DOUBLE_EQ(v.x(), 36.6 / 3.);
  ASSERT_DOUBLE_EQ(v.y(), -30.6 / 3.);
  ASSERT_DOUBLE_EQ(v.z(), 120.2586 / 3.);
  ASSERT_DOUBLE_EQ(v.w(), -0.5555555 / 3.);
}

TEST_F(Vector4Test, DevidesVectorByVector) {
  v = Vec4<double>(434.5, 93.5, 3858.53, -0.99999999);
  v = v / Vec4<double>(32.5, -16.2, 0.567, -999.99999999);
  ASSERT_DOUBLE_EQ(v.x(), 434.5 / 32.5);
  ASSERT_DOUBLE_EQ(v.y(), -93.5 / 16.2);
  ASSERT_DOUBLE_EQ(v.z(), 3858.53 / 0.567);
  ASSERT_DOUBLE_EQ(v[3], -0.99999999 / (-999.99999999));
}

TEST_F(Vector4Test, TestsEquality) {
  v = Vec4<double>(4.2, -6.54, 34855.38596, -0.9938375);
  ASSERT_TRUE(v == Vec4<double>(4.2, -6.54, 34855.38596, -0.9938375));
}

TEST_F(Vector4Test, TestsInequality) {
  v = Vec4<double>(4.2, -6.54, 0.0, 100.);
  ASSERT_TRUE(v != Vec4<double>(4.2, -4.36, 0.0, 100.));
}