#ifndef PUNCTUAL_LIGHT_H
#define PUNCTUAL_LIGHT_H

#include "light.h"
#include "core/math/vec3.h"

struct PunctualLight : Light
{
    vec3 color = vec3(1.0);
    PunctualLight() = default;
    PunctualLight(const json& j);
};

#endif