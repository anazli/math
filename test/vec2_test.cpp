#include "gtest/gtest.h"
#include "tools.h"

void comparePoints(const Point3D& p1, const Point3D& p2) {
  EXPECT_FLOAT_EQ(p1.x(), p2.x());
  EXPECT_FLOAT_EQ(p1.y(), p2.y());
  EXPECT_FLOAT_EQ(p1.z(), p2.z());
}

void comparePointsApprox(const Point3D& p1, const Point3D& p2, float eps) {
  EXPECT_NEAR(p1.x(), p2.x(), eps);
  EXPECT_NEAR(p1.y(), p2.y(), eps);
  EXPECT_NEAR(p1.z(), p2.z(), eps);
}

void compareVectors(const Vec3D& v1, const Vec3D& v2) {
  EXPECT_FLOAT_EQ(v1.x(), v2.x());
  EXPECT_FLOAT_EQ(v1.y(), v2.y());
  EXPECT_FLOAT_EQ(v1.z(), v2.z());
}

void compareVectorsApprox(const Vec3D& v1, const Vec3D& v2, float eps) {
  EXPECT_NEAR(v1.x(), v2.x(), eps);
  EXPECT_NEAR(v1.y(), v2.y(), eps);
  EXPECT_NEAR(v1.z(), v2.z(), eps);
}

class Vector2Test : public testing::Test {
 public:
  Vec2<double> v;
};

TEST_F(Vector2Test, CreatesVector) {
  v = Vec2<double>(0., 0.);
  ASSERT_DOUBLE_EQ(v.x(), 0.);
  ASSERT_DOUBLE_EQ(v.y(), 0.);
}

TEST_F(Vector2Test, AssertsOutOfBounds) {
  v = Vec2<double>(1., 2.);
  ASSERT_DEATH(v[2], "");
  ASSERT_DEATH(v[-1], "");
}

TEST_F(Vector2Test, SetsCoords) {
  v.setX(5.);
  v[1] = 4.;
  ASSERT_DOUBLE_EQ(v.x(), 5.);
  ASSERT_DOUBLE_EQ(v[1], 4.);
}

TEST_F(Vector2Test, SetXY) {
  v.set(-1.24, -5.54);
  ASSERT_DOUBLE_EQ(v.x(), -1.24);
  ASSERT_DOUBLE_EQ(v.y(), -5.54);

  v.set(6.68);
  ASSERT_DOUBLE_EQ(v.x(), 6.68);
  ASSERT_DOUBLE_EQ(v.y(), 6.68);
}

TEST_F(Vector2Test, ChangesSign) {
  v.set(-1.55);
  v = -v;
  ASSERT_DOUBLE_EQ(v[0], 1.55);
  ASSERT_DOUBLE_EQ(v[1], 1.55);
}

TEST_F(Vector2Test, AddsVectorOrNumber) {
  v = Vec2<double>(0., 0.);
  v = v + 4.46;
  ASSERT_DOUBLE_EQ(v.x(), 4.46);
  ASSERT_DOUBLE_EQ(v.y(), 4.46);

  v = v + Vec2<double>(4., 6.);
  ASSERT_DOUBLE_EQ(v.x(), 8.46);
  ASSERT_DOUBLE_EQ(v.y(), 10.46);
}

TEST_F(Vector2Test, SubtractsVectorOrNumber) {
  v = Vec2<double>(0., 0.);
  v = v - 4.46;
  ASSERT_DOUBLE_EQ(v.x(), -4.46);
  ASSERT_DOUBLE_EQ(v.y(), -4.46);

  v = v - Vec2<double>(4., 6.);
  ASSERT_DOUBLE_EQ(v.x(), -8.46);
  ASSERT_DOUBLE_EQ(v.y(), -10.46);
}

TEST_F(Vector2Test, GetsLenghtOfVector) {
  v = Vec2<double>(0., 0.);
  auto eps = 1E-6;
  ASSERT_DOUBLE_EQ(v.length(), 0.);
  v = Vec2<double>(1., 1.);
  EXPECT_NEAR(v.length(), sqrt(2.), eps);
  v = Vec2<double>(3., 3.);
  EXPECT_NEAR(v.length(), sqrt(18.), eps);
  v = Vec2<double>(-5., -5.);
  EXPECT_NEAR(v.length(), sqrt(50.), eps);
}

TEST_F(Vector2Test, MultipliesVectorWithNumber) {
  v = Vec2<double>(1., 0.);
  v = v * 5.;
  ASSERT_DOUBLE_EQ(v.x(), 5.);
  ASSERT_DOUBLE_EQ(v.y(), 0.);
}

TEST_F(Vector2Test, NormalizesVector) {
  v = Vec2<double>(4.53, 93.5);
  v.normalize();
  ASSERT_DOUBLE_EQ(v.length(), 1.);
}

TEST_F(Vector2Test, DotProduct) {
  v = Vec2<double>(3., 3.);
  ASSERT_DOUBLE_EQ(dot(v, Vec2<double>(3., 3.)), 18.);
  v = Vec2<double>(-1., 5.);
  ASSERT_DOUBLE_EQ(dot(v, Vec2<double>(-3., 3.)), 18.);
}

TEST_F(Vector2Test, GetUnitVectorOf) {
  v = Vec2<double>(4.36, 7.62);
  v = getUnitVectorOf(v);
  ASSERT_DOUBLE_EQ(v.length(), 1.);
}

TEST_F(Vector2Test, AddsTwoVectors) {
  v = Vec2<double>(4.532, 45.67);
  v = v + Vec2<double>(0.3456, 124.67);
  ASSERT_DOUBLE_EQ(v.x(), 4.8776);
  ASSERT_DOUBLE_EQ(v.y(), 170.34);
}

TEST_F(Vector2Test, SubtractsTwoVectors) {
  v = Vec2<double>(40.54, 2.4);
  v = v - Vec2<double>(4.20, -1.7);
  ASSERT_DOUBLE_EQ(v[0], 36.34);
  ASSERT_DOUBLE_EQ(v[1], 4.1);
}

TEST_F(Vector2Test, DevidesVectorByNumber) {
  v = Vec2<double>(36.6, -30.6);
  v = v / 3.;
  ASSERT_DOUBLE_EQ(v.x(), 36.6 / 3.);
  ASSERT_DOUBLE_EQ(v.y(), -30.6 / 3.);
}

TEST_F(Vector2Test, DevidesVectorByVector) {
  v = Vec2<double>(434.5, 93.5);
  v = v / Vec2<double>(32.5, -16.2);
  ASSERT_DOUBLE_EQ(v.x(), 434.5 / 32.5);
  ASSERT_DOUBLE_EQ(v.y(), -93.5 / 16.2);
}

TEST_F(Vector2Test, TestsEquality) {
  v = Vec2<double>(4.2, -6.54);
  ASSERT_TRUE(v == Vec2<double>(4.2, -6.54));
}

TEST_F(Vector2Test, TestsInequality) {
  v = Vec2<double>(4.2, -6.54);
  ASSERT_TRUE(v != Vec2<double>(-4.2, -4.36));
}