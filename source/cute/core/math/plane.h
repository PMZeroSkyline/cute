#ifndef PLANE_H
#define PLANE_H

#include "vec4.h"

struct Plane
{
    vec3 normal;
    float distance;
    Plane() {}
    Plane(const vec4& xyzw) : normal(xyzw.x, xyzw.y, xyzw.z), distance(xyzw.w) {}
    Plane(const vec3& _normal, float _distance) : normal(_normal), distance(_distance) {}
    Plane operator/(const float& s);
    Plane operator/(const float& s) const;
    float signed_distance(const vec3& point) const;
};
float length(const Plane &p);
Plane normalize(const Plane &p);

#endif