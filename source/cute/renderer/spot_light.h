#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "point_light.h"
#include "core/math/common.h"

struct SpotLight : PointLight
{
    float innerConeAngle = 0.f;
    float outerConeAngle = PI / 4.f;
    SpotLight() = default;
    SpotLight(const json& j);
    void to_json(json& j, const SpotLight& l);
    
};

#endif