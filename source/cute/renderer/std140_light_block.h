#ifndef STD140_LIGHT_BLOCK_H
#define STD140_LIGHT_BLOCK_H

#include "std140_directional_light.h"
#include "std140_point_light.h"
#include "std140_spot_light.h"
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