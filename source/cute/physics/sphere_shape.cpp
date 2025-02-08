#include "sphere_shape.h"

SphereShape::SphereShape(float _radius, const vec3& local_scale) : radius(_radius)
{
    bullet_shape = std::make_shared<btSphereShape>(radius);
    bullet_shape->setLocalScaling(*(btVector3*)&local_scale);
}
SphereShape::SphereShape(const json& j) : SphereShape(float(j["radius"])) {}
size_t SphereShape::hash(float _radius, const vec3& local_scale)
{
    size_t h1 = std::hash<float>{}(_radius);
    size_t h2 = std::hash<vec3>{}(local_scale);
    return h1 ^ (h2 << 1);
}
template struct std::hash<SphereShape>;