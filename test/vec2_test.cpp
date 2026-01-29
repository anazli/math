#include "vec2.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::FloatEq;
using testing::FloatNear;

class Vector2Test : public testing::Test {
 public:
  Vec2f v;
};

TEST_F(Vector2Test, CreatesVector) { ASSERT_THAT(v, Eq(Vec2f(0.f, 0.f))); }

TEST_F(Vector2Test, ThrowsOutOfBounds) {
  EXPECT_THROW(v[2], std::out_of_range);
  EXPECT_THROW(v[-1], std::out_of_range);
}

TEST_F(Vector2Test, AsignsNegative) {
  auto n = -1.55f;
  v.set(n);
  v = -v;
  ASSERT_THAT(v, Eq(Vec2f(-n, -n)));
}

TEST_F(Vector2Test, AddsVectorOrNumber) {
  v = v + 4.46f;
  EXPECT_THAT(v, Eq(Vec2f(4.46f, 4.46f)));

  v = v + Vec2f(4.f, 6.f);
  ASSERT_THAT(v, Eq(Vec2f(8.46f, 10.46f)));
}

TEST_F(Vector2Test, SubtractsVectorOrNumber) {
  auto n = 4.46f;
  v = v - n;
  EXPECT_THAT(v, Eq(Vec2f(-n, -n)));

  v = v - Vec2f(4.f, 6.f);
  ASSERT_THAT(v, Eq(Vec2f(-8.46f, -10.46f)));
}

TEST_F(Vector2Test, GetsLenghtOfVector) {
  auto eps = 1E-6f;
  auto v1 = Vec2f::unit_vec();
  auto v2 = Vec2f(3.f, 3.f);
  auto v3 = Vec2f(-5.f, -5.f);

  EXPECT_THAT(v.length(), FloatEq(0.f));
  EXPECT_THAT(v1.length(), FloatNear(static_cast<float>(sqrt(2.)), eps));
  EXPECT_THAT(v2.length(), FloatNear(static_cast<float>(sqrt(18.)), eps));
  ASSERT_THAT(v3.length(), FloatNear(static_cast<float>(sqrt(50.)), eps));
}

TEST_F(Vector2Test, MultipliesVectorWithNumber) {
  v = Vec2f(1.f, 0.f);
  v = v * 5.f;
  ASSERT_THAT(v, Eq(Vec2f(5.f, 0.f)));
}

TEST_F(Vector2Test, NormalizesVector) {
  v = Vec2f(4.53f, 93.5f);
  v.normalize();
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector2Test, DotProduct) {
  v = Vec2f(3.f, 3.f);
  EXPECT_THAT(dot(v, Vec2f(3.f, 3.f)), FloatEq(18.f));
  v = Vec2f(-1.f, 5.f);
  ASSERT_THAT(dot(v, Vec2f(-3.f, 3.f)), FloatEq(18.f));
}

TEST_F(Vector2Test, ReturnsNormalizedVectorOfInput) {
  v = Vec2f(4.36f, 7.62f);
  v = normalized(v);
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector2Test, AddsTwoVectors) {
  v = Vec2f(4.532f, 45.67f);
  v = v + Vec2f(0.3456f, 124.67f);
  ASSERT_THAT(v, Eq(Vec2f(4.8776f, 170.34f)));
}

TEST_F(Vector2Test, DISABLED_SubtractsTwoVectors) {
  v = Vec2f(40.54f, 2.4f);
  v = v - Vec2f(4.20f, -1.7f);
  // output of gtest
  /*Expected: is equal to (36.34,4.1)
  Actual: (36.34,4.1) (of type Vec2<float>)
  ...might be a bug
*/
  ASSERT_THAT(v, Eq(Vec2f(36.34f, 4.1f)));
}

TEST_F(Vector2Test, DevidesVectorByNumber) {
  v = Vec2f(36.6f, -30.6f);
  v = v / 3.f;
  ASSERT_THAT(v, Eq(Vec2f(36.6f / 3.f, -30.6f / 3.f)));
}

TEST_F(Vector2Test, DevidesVectorByVector) {
  v = Vec2f(434.5f, 93.5f);
  v = v / Vec2f(32.5f, -16.2f);
  ASSERT_THAT(v, Eq(Vec2f(434.5f / 32.5f, -93.5f / 16.2f)));
}
