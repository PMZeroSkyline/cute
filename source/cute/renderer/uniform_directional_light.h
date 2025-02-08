#ifndef UNIFFORM_DIRECTIONAL_LIGHT_H
#define UNIFFORM_DIRECTIONAL_LIGHT_H

#include "core/math/vec3.h"
namespace std140
{
    struct DirectionalLight
    {
        vec3 direction;
        float padding;
        vec3 color;
        float intensity;
        DirectionalLight() = default;
        DirectionalLight(const vec3 &_direction, const vec3 &_color, float _intensity);
    };
}
#endif