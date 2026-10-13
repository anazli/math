#pragma once

#include "point3.h"
#include "vec3.h"

class Ray {
 public:
  constexpr Ray() = default;
  constexpr Ray(const Point3f &origin, const Vec3f &direction)
      : m_origin(origin), m_direction(direction) {}

  constexpr void setOrigin(const Point3f &origin) { m_origin = origin; }
  constexpr void setDirection(const Vec3f &direction) {
    m_direction = direction;
  }
  constexpr Point3f origin() const { return m_origin; }
  constexpr Vec3f direction() const { return m_direction; }
  constexpr Point3f position(const float &parameter) const {
    return origin() + parameter * direction();
  }

  constexpr void setMinRange(float t) { m_min_parameter = t; }
  constexpr float getMinRange() const { return m_min_parameter; }
  constexpr void setMaxRange(float t) { m_max_parameter = t; }
  constexpr float getMaxRange() const { return m_max_parameter; }

 private:
  Point3f m_origin;
  Vec3f m_direction;
  mutable float m_min_parameter = 0.01f;
  mutable float m_max_parameter = std::numeric_limits<float>::infinity();
};