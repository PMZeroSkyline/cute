#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "punctual_light.h"

struct DirectionalLight : PunctualLight
{
    DirectionalLight() = default;
    DirectionalLight(const json& j);
};
void to_json(json& j, const DirectionalLight& l);

#endif