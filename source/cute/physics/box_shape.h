#ifndef BOX_SHAPE_H
#define BOX_SHAPE_H

#include "shape.h"
#include "core/parser/json.h"
#include "core/math/vec3.h"

struct BoxShape : Shape
{
    vec3 size;
    BoxShape() = default;
    BoxShape(const vec3& _size, const vec3& local_scale = vec3(1.f));
    BoxShape(const json& j);
    static size_t hash(const vec3& _size, const vec3& local_scale);
    static inline std::unordered_map<size_t, std::weak_ptr<BoxShape>> weak;
};
template <>
struct std::hash<BoxShape> {
    size_t operator()(const BoxShape& s) const {
        return BoxShape::hash(s.size, *(vec3*)&s.bullet_shape->getLocalScaling());
    }
};
#endif