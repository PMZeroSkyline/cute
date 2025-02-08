#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "platform/physics_wrapper.h"
#include "core/math/mat4.h"

struct Transform
{
    vec3 position;
    quat rotation;
    vec3 scale;
    Transform();
    Transform(const vec3 t, const quat r, const vec3 s);
    Transform(const mat4 &matrix);
    mat4 to_matrix() const;
};
std::ostream &operator<<(std::ostream &os, const Transform &t);

#endif
