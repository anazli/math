#include "vec2.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::FloatEq;
using testing::FloatNear;

MATCHER_P2(Vec2Near, v, eps, "") {
  return fabs(arg.x - v.x) < eps && fabs(arg.y - v.y) < eps;
}

class Vector2Test : public testing::Test {
 public:
  Vec2f v;
  float eps = 1E-6f;
};

TEST_F(Vector2Test, CreatesVector) { ASSERT_THAT(v, Eq(Vec2f(0.f, 0.f))); }

TEST_F(Vector2Test, AsignsNegative) {
  constexpr auto n = -1.55f;
  constexpr auto result = -Vec2f(n, n);
  ASSERT_THAT(result, Eq(Vec2f(-n, -n)));
}

TEST_F(Vector2Test, AddsVectorOrNumber) {
  constexpr auto v1 = Vec2f{} + 4.46f;
  constexpr auto v2 = v1 + Vec2f(4.f, 6.f);
  EXPECT_THAT(v1, Eq(Vec2f(4.46f, 4.46f)));

  ASSERT_THAT(v2, Eq(Vec2f(8.46f, 10.46f)));
}

TEST_F(Vector2Test, SubtractsVectorOrNumber) {
  constexpr auto n = 4.46f;
  constexpr auto v1 = Vec2f{} - n;
  constexpr auto v2 = v1 - Vec2f(4.f, 6.f);
  EXPECT_THAT(v1, Eq(Vec2f(-n, -n)));

  ASSERT_THAT(v2, Eq(Vec2f(-8.46f, -10.46f)));
}

TEST_F(Vector2Test, GetsLenghtOfVector) {
  constexpr auto v1 = Vec2f::create_unit_vec();
  constexpr auto v2 = Vec2f(3.f, 3.f);
  constexpr auto v3 = Vec2f(-5.f, -5.f);

  EXPECT_THAT(v.length(), FloatEq(0.f));
  EXPECT_THAT(v1.length(), FloatNear(static_cast<float>(sqrt(2.)), eps));
  EXPECT_THAT(v2.length(), FloatNear(static_cast<float>(sqrt(18.)), eps));
  ASSERT_THAT(v3.length(), FloatNear(static_cast<float>(sqrt(50.)), eps));
}

TEST_F(Vector2Test, MultipliesVectorWithNumber) {
  constexpr auto result = Vec2f(1.f, 0.f) * 5.f;
  ASSERT_THAT(result, Eq(Vec2f(5.f, 0.f)));
}

TEST_F(Vector2Test, NormalizesVector) {
  v = Vec2f(4.53f, 93.5f);
  v.normalize();
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector2Test, DotProduct) {
  constexpr auto result1 = dot(Vec2f(3.f, 3.f), Vec2f(3.f, 3.f));
  constexpr auto result2 = dot(Vec2f(-1.f, 5.f), Vec2f(-3.f, 3.f));
  EXPECT_THAT(result1, FloatEq(18.f));
  ASSERT_THAT(result2, FloatEq(18.f));
}

TEST_F(Vector2Test, ReturnsNormalizedVectorOfInput) {
  v = Vec2f(4.36f, 7.62f);
  v = normalized(v);
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector2Test, AddsTwoVectors) {
  constexpr auto result = Vec2f(4.532f, 45.67f) + Vec2f(0.3456f, 124.67f);
  ASSERT_THAT(result, Eq(Vec2f(4.8776f, 170.34f)));
}

TEST_F(Vector2Test, SubtractsTwoVectors) {
  constexpr auto result = Vec2f(40.54f, 2.4f) - Vec2f(4.20f, -1.7f);
  ASSERT_THAT(result, Vec2Near(Vec2f(36.34f, 4.1f), eps));
}

TEST_F(Vector2Test, DevidesVectorByNumber) {
  constexpr auto result = Vec2f(36.6f, -30.6f) / 3.f;
  ASSERT_THAT(result, Eq(Vec2f(36.6f / 3.f, -30.6f / 3.f)));
}

TEST_F(Vector2Test, DevidesVectorByVector) {
  constexpr auto result = Vec2f(434.5f, 93.5f) / Vec2f(32.5f, -16.2f);
  ASSERT_THAT(result, Eq(Vec2f(434.5f / 32.5f, -93.5f / 16.2f)));
}
