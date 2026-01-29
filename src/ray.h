#pragma once

#include "point3.h"
#include "vec3.h"

class Ray {
 public:
  Ray() = default;
  Ray(const Point3f &origin, const Vec3f &direction)
      : m_origin(origin), m_direction(direction) {}

  void setOrigin(const Point3f &origin) { m_origin = origin; }
  void setDirection(const Vec3f &direction) { m_direction = direction; }
  Point3f origin() const { return m_origin; }
  Vec3f direction() const { return m_direction; }
  Point3f position(const float &parameter) const {
    return origin() + parameter * direction();
  }

  void setMaxRange(float t) { m_max_parameter = t; }
  float getMaxRange(float t) const { return m_max_parameter; }

 private:
  Point3f m_origin;
  Vec3f m_direction;
  mutable float m_max_parameter = std::numeric_limits<float>::infinity();
};
