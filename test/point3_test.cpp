#include "point3.h"

#include "gtest/gtest.h"
#include "vec3.h"

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

class Point3Test : public testing::Test {
 public:
  Point3<int> p;
};

TEST_F(Point3Test, createsPoint) {
  p = Point3<int>();
  ASSERT_EQ(p.x(), 0);
  ASSERT_EQ(p.y(), 0);
  ASSERT_EQ(p.z(), 0);
  p = Point3<int>(1, -8, 0);
  ASSERT_EQ(p.x(), 1);
  ASSERT_EQ(p.y(), -8);
  ASSERT_EQ(p.z(), 0);
  p = Point3<int>(9, 0, 0);
  ASSERT_EQ(p.x(), 9);
  ASSERT_EQ(p.y(), 0);
  ASSERT_EQ(p.z(), 0);
}

TEST_F(Point3Test, subtractsPointFromPoint) {
  Point3D pf = Point3D(1, 0, 4);
  Point3D p1 = Point3D(0, 2, 4);
  Vec3f v = p1 - pf;
  ASSERT_EQ(v.x(), -1);
  ASSERT_EQ(v.y(), 2);
  ASSERT_EQ(v.z(), 0);
  ASSERT_FLOAT_EQ(v.length(), sqrt(5));
}

TEST_F(Point3Test, subtractsVectorFromPoint) {
  p = Point3<int>(3, 4, 5);
  auto v = Vec3<int>(3, 4, 5);
  p = p - v;
  ASSERT_EQ(p.x(), 0);
  ASSERT_EQ(p.y(), 0);
  ASSERT_EQ(p.z(), 0);
}

TEST_F(Point3Test, addsVectorToPoint) {
  p = Point3<int>(0, -1, -8);
  auto v = Vec3<int>(-4, 5, 9);
  p = p + v;
  ASSERT_EQ(p.x(), -4);
  ASSERT_EQ(p.y(), 4);
  ASSERT_EQ(p.z(), 1);
}