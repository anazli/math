#include "vec4.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::FloatEq;

MATCHER_P2(Vec4Near, v, eps, "") {
  return fabs(arg.x - v.x) < eps && fabs(arg.y - v.y) < eps &&
         fabs(arg.z - v.z) < eps && fabs(arg.w - v.w) < eps;
}

class Vector4Test : public testing::Test {
 public:
  Vec4f v;
  float eps = 1E-6f;
};

TEST_F(Vector4Test, CreatesVector) { ASSERT_THAT(v, Eq(Vec4f())); }

TEST_F(Vector4Test, AssertsOutOfBounds) {
  EXPECT_THROW(v[4], std::out_of_range);
  ASSERT_THROW(v[-1], std::out_of_range);
}

TEST_F(Vector4Test, SetsCoords) {
  v.x = 5.f;
  v[1] = 4.f;
  v[2] = 0.2f;
  v.w = -5.2f;
  ASSERT_THAT(v, Eq(Vec4f(5.f, 4.f, 0.2f, -5.2f)));
}

TEST_F(Vector4Test, ChangesSign) {
  constexpr auto n = 1.55f;
  constexpr auto result = -Vec4f(-n, -n, -n, -n);
  ASSERT_THAT(result, Eq(Vec4f(n, n, n, n)));
}

TEST_F(Vector4Test, AddsVectorOrNumber) {
  constexpr auto v1 = Vec4f(0.f, 0.f, 5.f, 3.5f) + 4.46f;
  constexpr auto v2 = v1 + Vec4f(4.f, 6.f, 0.f, 45.f);

  EXPECT_THAT(v1, Eq(Vec4f(4.46f, 4.46f, 9.46f, 7.96f)));
  ASSERT_THAT(v2, Eq(Vec4f(8.46f, 10.46f, 9.46f, 52.96f)));
}

TEST_F(Vector4Test, SubtractsVectorOrNumber) {
  constexpr auto v1 = Vec4f(0.f, 0.f, 3.f, -5.5f) - 4.46f;
  constexpr auto v2 = v1 - Vec4f(4.f, 6.f, 0.f, -1.2f);

  EXPECT_THAT(v1, Eq(Vec4f(-4.46f, -4.46f, -1.46f, -9.96f)));
  ASSERT_THAT(v2, Eq(Vec4f(-8.46f, -10.46f, -1.46f, -8.76f)));
}

TEST_F(Vector4Test, GetsLenghtOfVector) {
  auto v1 = Vec4f::create_unit_vec();
  auto v2 = Vec4f(3.f, 3.f, 3.f, 3.f);
  auto v3 = Vec4f(-5.f, -5.f, 5.f, 5.f);
  EXPECT_THAT(v.length(), FloatEq(0.f));
  EXPECT_THAT(v1.length(), FloatEq(sqrt(4.f)));
  EXPECT_THAT(v2.length(), FloatEq(sqrt(36.f)));
  ASSERT_THAT(v3.length(), FloatEq(sqrt(100.f)));
}

TEST_F(Vector4Test, MultipliesVectorWithNumber) {
  constexpr auto result = Vec4f(1.f, 0.f, 5.f, -9.f) * 5.f;
  ASSERT_THAT(result, Eq(Vec4f(5.f, 0.f, 25.f, -45.f)));
}

TEST_F(Vector4Test, NormalizesVector) {
  v = Vec4f(4.53f, 93.5f, -56.3f, -100.00001f);
  v.normalize();
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector4Test, CalculatesDotProduct) {
  constexpr auto result1 =
      dot(Vec4f(3.f, 3.f, 4.f, 1.f), Vec4f(3.f, 3.f, 9.f, -10.f));
  constexpr auto result2 =
      dot(Vec4f(-1.f, 5.f, 9.f, -3.f), Vec4f(-3.f, 3.f, 6.f, 0.f));
  EXPECT_THAT(result1, FloatEq(44.f));
  ASSERT_THAT(result2, FloatEq(72.f));
}

TEST_F(Vector4Test, GetsNormalizedVectorOfAnother) {
  v = Vec4f(4.36f, 7.62f, 0.466f, -30485.55555555f);
  v = normalized(v);
  ASSERT_THAT(v.length(), FloatEq(1.f));
}

TEST_F(Vector4Test, AddsTwoVectors) {
  constexpr auto result =
      Vec4f(4.532f, 45.67f, 0.83f, -44.6f) + Vec4f(0.3456f, 124.67f, 1.f, 9.f);
  ASSERT_THAT(result, Vec4Near(Vec4f(4.8776f, 170.34f, 1.83f, -35.6f), eps));
}

TEST_F(Vector4Test, SubtractsTwoVectors) {
  constexpr auto result =
      Vec4f(40.54f, 2.4f, 0.62f, 0.f) - Vec4f(4.20f, -1.7f, -1.f, -99.99999f);
  ASSERT_THAT(result, Vec4Near(Vec4f(36.34f, 4.1f, 1.62f, 99.99999f), eps));
}

TEST_F(Vector4Test, DevidesVectorByNumber) {
  constexpr auto result = Vec4f(36.6f, -30.6f, 120.2586f, -0.5555555f) / 3.f;
  ASSERT_THAT(result, Eq(Vec4f(36.6f / 3.f, -30.6f / 3.f, 120.2586f / 3.f,
                               -0.5555555f / 3.f)));
}

TEST_F(Vector4Test, DevidesVectorByVector) {
  constexpr auto result = Vec4f(434.5f, 93.5f, 3858.53f, -0.99999999f) /
                          Vec4f(32.5f, -16.2f, 0.567f, -999.99999999f);
  ASSERT_THAT(result,
              Eq(Vec4f(434.5f / 32.5f, -93.5f / 16.2f, 3858.53f / 0.567f,
                       -0.99999999f / (-999.99999999f))));
}

TEST_F(Vector4Test, TestsEquality) {
  constexpr auto value = Vec4f(4.2f, -6.54f, 34855.38596f, -0.9938375f);
  ASSERT_THAT(value, Eq(Vec4f(4.2f, -6.54f, 34855.38596f, -0.9938375f)));
}

TEST_F(Vector4Test, TestsInequality) {
  constexpr auto value = Vec4f(4.2, -6.54, 0.0, 100.);
  ASSERT_THAT(value, testing::Ne(Vec4f(4.2f, -4.36f, 0.0f, 100.f)));
}