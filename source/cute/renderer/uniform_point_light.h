#ifndef UNIFORM_POINT_LIGHT_H
#define UNIFORM_POINT_LIGHT_H

#include "core/math/vec3.h"

namespace std140
{
    struct PointLight
    {
        vec3 position;
        float range;
        vec3 color;
        float intensity;
        PointLight() = default;
        PointLight(const vec3 &_position, const vec3 &_color, float _intensity, float _range);
    };
}
#endif
