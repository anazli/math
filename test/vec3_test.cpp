#include "vec3.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::FloatEq;
using testing::FloatNear;
using testing::Ne;

MATCHER_P2(Vec3Near, v, eps, "") {
  return fabs(arg.x() - v.x()) < eps && fabs(arg.y() - v.y()) < eps &&
         fabs(arg.z() - v.z()) < eps;
}

class Vector3Test : public testing::Test {
 public:
  Vec3f v;
  float eps = 1E-6f;
};

TEST_F(Vector3Test, CreatesVector) { ASSERT_THAT(v, Eq(Vec3f())); }

TEST_F(Vector3Test, AssertsOutOfBounds) {
  v = Vec3f(1.f, 2.f, 0.5f);
  EXPECT_THROW(v[3], std::out_of_range);
  ASSERT_THROW(v[-1], std::out_of_range);
}

TEST_F(Vector3Test, SetsCoords) {
  v.x(5.);
  v[1] = 4.;
  v[2] = 0.2;
  ASSERT_THAT(v, Eq(Vec3f(5.f, 4.f, 0.2f)));
}

TEST_F(Vector3Test, ChangesSign) {
  v.set(-1.55);
  v = -v;
  ASSERT_THAT(v, Eq(Vec3f(1.55f, 1.55f, 1.55f)));
}

TEST_F(Vector3Test, AddsVectorOrNumber) {
  v = Vec3f(0.f, 0.f, 5.f);
  v = v + 4.46f;
  EXPECT_THAT(v, Eq(Vec3f(4.46f, 4.46f, 9.46f)));

  v = v + Vec3f(4.f, 6.f, 0.f);
  ASSERT_THAT(v, Eq(Vec3f(8.46f, 10.46f, 9.46f)));
}

TEST_F(Vector3Test, SubtractsVectorOrNumber) {
  v = Vec3f(0.f, 0.f, 3.f);
  v = v - 4.46f;
  EXPECT_THAT(v, Eq(Vec3f(-4.46f, -4.46f, -1.46f)));

  v = v - Vec3f(4.f, 6.f, 0.f);
  ASSERT_THAT(v, Eq(Vec3f(-8.46f, -10.46f, -1.46f)));
}

TEST_F(Vector3Test, GetsLenghtOfVector) {
  v = Vec3f(0.f, 0.f, 0.f);
  auto v1 = Vec3f(1.f, 1.f, 1.f);
  auto v2 = Vec3f(3.f, 3.f, 3.f);
  auto v3 = Vec3f(-5.f, -5.f, 5.f);

  EXPECT_THAT(v.length(), FloatEq(0.f));
  EXPECT_THAT(v1.length(), FloatEq(sqrt(3.f)));
  EXPECT_THAT(v2.length(), FloatEq(sqrt(27.f)));
  EXPECT_THAT(v3.length(), FloatEq(sqrt(75.f)));
}

TEST_F(Vector3Test, MultipliesVectorWithNumber) {
  v = Vec3f(1.f, 0.f, 5.f) * 5.f;
  ASSERT_THAT(v, Eq(Vec3f(5.f, 0.f, 25.f)));
}

TEST_F(Vector3Test, NormalizesVector) {
  v = Vec3f(4.53f, 93.5f, -56.3f);
  v.normalize();
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector3Test, CalculatesDotProduct) {
  v = Vec3f(3.f, 3.f, 4.f);
  auto v1 = Vec3f(-1.f, 5.f, 9.f);

  EXPECT_THAT(dot(v, Vec3f(3.f, 3.f, 9.f)), FloatEq(54.f));
  ASSERT_THAT(dot(v1, Vec3f(-3.f, 3.f, 6.f)), FloatEq(72.f));
}

TEST_F(Vector3Test, GetUnitVectorOf) {
  v = Vec3f(4.36f, 7.62f, 0.466f);
  v = normalized(v);
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector3Test, AddsTwoVectors) {
  v = Vec3f(4.532f, 45.67f, 0.83f);
  v = v + Vec3f(0.3456f, 124.67f, 1.f);
  ASSERT_THAT(v, Vec3Near(Vec3f(4.8776f, 170.34f, 1.83f), eps));
}

TEST_F(Vector3Test, SubtractsTwoVectors) {
  v = Vec3f(40.54f, 2.4f, 0.62f);
  v = v - Vec3f(4.20f, -1.7f, -1.f);
  ASSERT_THAT(v, Vec3Near(Vec3f(36.34f, 4.1f, 1.62f), eps));
}

TEST_F(Vector3Test, DevidesVectorByNumber) {
  v = Vec3f(36.6f, -30.6f, 120.2586f);
  v = v / 3.f;
  ASSERT_THAT(v, Eq(Vec3f(36.6f / 3.f, -30.6f / 3.f, 120.2586f / 3.f)));
}

TEST_F(Vector3Test, DevidesVectorByVector) {
  v = Vec3f(434.5f, 93.5f, 3858.53f);
  v = v / Vec3f(32.5f, -16.2f, 0.567f);
  ASSERT_THAT(v, Eq(Vec3f(434.5f / 32.5f, -93.5f / 16.2f, 3858.53f / 0.567f)));
}

TEST_F(Vector3Test, TestsEquality) {
  v = Vec3f(4.2f, -6.54f, 34855.38596f);
  ASSERT_THAT(v, Eq(Vec3f(4.2f, -6.54f, 34855.38596f)));
}

TEST_F(Vector3Test, TestsInequality) {
  v = Vec3f(4.2f, -6.54f, 0.f);
  ASSERT_THAT(v, Ne(Vec3f(4.2f, -4.36f, 0.f)));
}

TEST_F(Vector3Test, reflectsVector1) {
  v = Vec3f(1.f, -1.f, 0.f);
  Vec3f n(0.f, 1.f, 0.f);
  Vec3f r = reflect(v, n);
  ASSERT_THAT(r, Eq(Vec3f(1.f, 1.f, 0.f)));
}

TEST_F(Vector3Test, reflectsVector2) {
  v = Vec3f(0.f, -1.f, 0.f);
  Vec3f n(sqrt(2.f) / 2.f, sqrt(2.f) / 2.f, 0.f);
  Vec3f r = reflect(v, n);
  ASSERT_THAT(r, Vec3Near(Vec3f(1.f, 0.f, 0.f), eps));
}