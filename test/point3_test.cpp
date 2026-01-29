#include "point3.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "vec3.h"

using testing::Eq;
using testing::FloatEq;

class Point3Test : public testing::Test {
 public:
  Point3f p;
};

TEST_F(Point3Test, createsPoint) { ASSERT_THAT(p, Eq(Point3f())); }

TEST_F(Point3Test, subtractsPointFromPoint) {
  auto pf = Point3f(1.f, 0.f, 4.f);
  auto p1 = Point3f(0.f, 2.f, 4.f);
  Vec3f v = p1 - pf;
  EXPECT_THAT(v, Vec3f(-1.f, 2.f, 0.f));
  ASSERT_THAT(v.length(), FloatEq(sqrt(5.f)));
}

TEST_F(Point3Test, subtractsVectorFromPoint) {
  p = Point3f(3.f, 4.f, 5.f);
  auto v = Vec3f(3.f, 4.f, 5.f);
  p = p - v;
  ASSERT_THAT(p, Eq(Point3f()));
}

TEST_F(Point3Test, addsVectorToPoint) {
  p = Point3f(0.f, -1.f, -8.f);
  auto v = Vec3f(-4.f, 5.f, 9.f);
  p = p + v;
  ASSERT_THAT(p, Eq(Point3f(-4.f, 4.f, 1.f)));
}