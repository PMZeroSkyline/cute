#ifndef UNIFORM_LIGHT_BLOCK_H
#define UNIFORM_LIGHT_BLOCK_H

#include "uniform_directional_light.h"
#include "uniform_point_light.h"
#include "uniform_spot_light.h"
#include "core/math/vec4.h"

namespace std140
{
    struct LightBlock
    {
        DirectionalLight iDirectionalLights[4];
        PointLight iPointLights[4];
        SpotLight iSpotLights[4];
        vec4 iIrradianceCoefficients[9];
        vec4 iLightSize;
        float iImageBasedLightIntensity;
    };
}
#endif