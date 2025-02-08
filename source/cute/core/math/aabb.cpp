#include "aabb.h"

AABB::AABB(const vec3& _center, const vec3& _extent) : center(_center), extent(_extent) {}
AABB AABB::construct(const vec3& _min, const vec3& _max)
{
    return AABB((_min + _max) / 2.f, (_max - _min) / 2.f);
}
std::shared_ptr<AABB> AABB::make(const vec3& _min, const vec3& _max)
{
    return std::make_shared<AABB>((_min + _max) / 2.f, (_max - _min) / 2.f);
}
vec3 AABB::get_min() const
{
    return center - extent;
}
vec3 AABB::get_max() const
{
    return center + extent;
}
float AABB::signed_distance(const vec3& point) const
{
    // https://iquilezles.org/articles/distfunctions/
    vec3 q = abs(point - center) - extent;
    return length(max(q, 0.f)) + std::min(std::max(q.x, std::max(q.y, q.z)), 0.f);
}
AABB operator*(const mat4 &M, const AABB& bbox)
{
    const vec3 c = M * vec4(bbox.center, 1.f);
    const vec3 wX = M.col(0) * bbox.extent.x;
    const vec3 wY = M.col(1) * bbox.extent.y;
    const vec3 wZ = M.col(2) * bbox.extent.z;
    const vec3 e = abs(wX) + abs(wY) + abs(wZ);
    return AABB(c, e);
}
