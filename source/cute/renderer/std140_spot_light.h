#ifndef STD140_SPOT_LIGHT_H
#define STD140_SPOT_LIGHT_H
#include "core/math/vec3.h"
namespace std140
{
    struct SpotLight
    {
        vec3 position;
        float range;
        vec3 direction;
        float intensity;
        vec3 color;
        float angleScale;
        float angleOffset;
        vec3 padding;
        SpotLight() = default;
        SpotLight(const vec3 &_position, const vec3 &_direction, const vec3 &_color, float _intensity, float _range, float innerConeAngle, float outerConeAngle);
    };
}
#endif