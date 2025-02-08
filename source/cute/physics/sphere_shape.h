#ifndef SPHERE_SHAPE_H
#define SPHERE_SHAPE_H

#include "shape.h"
#include "core/math/vec3.h"
#include "core/parser/json.h"
#include <unordered_map>

struct SphereShape : Shape
{
    float radius;
    SphereShape() = default;
    SphereShape(float _radius, const vec3& local_scale = vec3(1.f));
    SphereShape(const json& j);
    static size_t hash(float _radius, const vec3& local_scale);
    static inline std::unordered_map<size_t, std::weak_ptr<SphereShape>> weak;
};
template <>
struct std::hash<SphereShape> {
    size_t operator()(const SphereShape& s) const {
        return SphereShape::hash(s.radius, *(vec3*)&s.bullet_shape->getLocalScaling());
    }
};
#endif