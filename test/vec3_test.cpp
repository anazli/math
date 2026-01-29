#include "vec3.h"

#include "gtest/gtest.h"

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

class Vector3Test : public testing::Test {
 public:
  Vec3D v;
};

TEST_F(Vector3Test, CreatesVector) {
  v = Vec3D(0.f, 0.f, 0.f);
  compareVectors(v, Vec3D());
}

TEST_F(Vector3Test, AssertsOutOfBounds) {
  v = Vec3D(1.f, 2.f, 0.5f);
  ASSERT_DEATH(v[3], "");
  ASSERT_DEATH(v[-1], "");
}

TEST_F(Vector3Test, SetsCoords) {
  v.x(5.);
  v[1] = 4.;
  v[2] = 0.2;
  compareVectors(v, Vec3D(5.f, 4.f, 0.2f));
}

TEST_F(Vector3Test, SetXYZ) {
  v.set(-1.24f, -5.54f, 45.6f);
  compareVectors(v, Vec3D(-1.24f, -5.54f, 45.6f));

  v.set(6.68f);
  compareVectors(v, Vec3D(6.68f, 6.68f, 6.68f));
}

TEST_F(Vector3Test, ChangesSign) {
  v.set(-1.55);
  v = -v;
  compareVectors(v, Vec3D(1.55f, 1.55f, 1.55f));
}

TEST_F(Vector3Test, AddsVectorOrNumber) {
  v = Vec3D(0.f, 0.f, 5.f);
  v = v + 4.46f;
  compareVectors(v, Vec3D(4.46f, 4.46f, 9.46f));

  v = v + Vec3D(4.f, 6.f, 0.f);
  compareVectors(v, Vec3D(8.46f, 10.46f, 9.46f));
}

TEST_F(Vector3Test, SubtractsVectorOrNumber) {
  v = Vec3D(0.f, 0.f, 3.f);
  v = v - 4.46f;
  compareVectors(v, Vec3D(-4.46f, -4.46f, -1.46f));

  v = v - Vec3D(4.f, 6.f, 0.f);
  compareVectors(v, Vec3D(-8.46f, -10.46f, -1.46f));
}

TEST_F(Vector3Test, GetsLenghtOfVector) {
  v = Vec3D(0.f, 0.f, 0.f);
  ASSERT_FLOAT_EQ(v.length(), 0.f);
  v = Vec3D(1.f, 1.f, 1.f);
  ASSERT_FLOAT_EQ(v.length(), sqrt(3.f));
  v = Vec3D(3.f, 3.f, 3.f);
  ASSERT_FLOAT_EQ(v.length(), sqrt(27.f));
  v = Vec3D(-5.f, -5.f, 5.f);
  ASSERT_FLOAT_EQ(v.length(), sqrt(75.f));
}

TEST_F(Vector3Test, MultipliesVectorWithNumber) {
  v = Vec3D(1.f, 0.f, 5.f) * 5.f;
  compareVectors(v, Vec3D(5.f, 0.f, 25.f));
}

TEST_F(Vector3Test, NormalizesVector) {
  v = Vec3D(4.53f, 93.5f, -56.3f);
  v.normalize();
  ASSERT_DOUBLE_EQ(v.length(), 1.f);
}

TEST_F(Vector3Test, DotProduct) {
  v = Vec3D(3.f, 3.f, 4.f);
  ASSERT_DOUBLE_EQ(dot(v, Vec3D(3.f, 3.f, 9.f)), 54.f);
  v = Vec3D(-1.f, 5.f, 9.f);
  ASSERT_FLOAT_EQ(dot(v, Vec3D(-3.f, 3.f, 6.f)), 72.f);
}

TEST_F(Vector3Test, GetUnitVectorOf) {
  v = Vec3D(4.36f, 7.62f, 0.466f);
  v = normalized(v);
  ASSERT_FLOAT_EQ(v.length(), 1.f);
}

TEST_F(Vector3Test, AddsTwoVectors) {
  v = Vec3D(4.532f, 45.67f, 0.83f);
  v = v + Vec3D(0.3456f, 124.67f, 1.f);
  compareVectors(v, Vec3D(4.8776f, 170.34f, 1.83f));
}

TEST_F(Vector3Test, SubtractsTwoVectors) {
  v = Vec3D(40.54f, 2.4f, 0.62f);
  v = v - Vec3D(4.20f, -1.7f, -1.f);
  compareVectors(v, Vec3D(36.34f, 4.1f, 1.62f));
}

TEST_F(Vector3Test, DevidesVectorByNumber) {
  v = Vec3D(36.6f, -30.6f, 120.2586f);
  v = v / 3.f;
  compareVectors(v, Vec3D(36.6f / 3.f, -30.6f / 3.f, 120.2586f / 3.f));
}

TEST_F(Vector3Test, DevidesVectorByVector) {
  v = Vec3D(434.5f, 93.5f, 3858.53f);
  v = v / Vec3D(32.5f, -16.2f, 0.567f);
  compareVectors(v, Vec3D(434.5f / 32.5f, -93.5f / 16.2f, 3858.53f / 0.567f));
}

TEST_F(Vector3Test, TestsEquality) {
  v = Vec3D(4.2f, -6.54f, 34855.38596f);
  ASSERT_TRUE(v == Vec3D(4.2f, -6.54f, 34855.38596f));
}

TEST_F(Vector3Test, TestsInequality) {
  v = Vec3D(4.2f, -6.54f, 0.f);
  ASSERT_TRUE(v != Vec3D(4.2f, -4.36f, 0.f));
}

TEST_F(Vector3Test, reflectsVector1) {
  v = Vec3D(1.f, -1.f, 0.f);
  Vec3D n(0.f, 1.f, 0.f);
  Vec3D r = reflect(v, n);
  ASSERT_TRUE(r == Vec3D(1.f, 1.f, 0.f));
}

TEST_F(Vector3Test, reflectsVector2) {
  v = Vec3D(0.f, -1.f, 0.f);
  Vec3D n(sqrt(2.f) / 2.f, sqrt(2.f) / 2.f, 0.f);
  Vec3D r = reflect(v, n);

  double eps = 10.E-8f;
  compareVectorsApprox(r, Vec3D(1.f, 0.f, 0.f), eps);
}