#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "punctual_light.h"

struct PointLight : PunctualLight
{
    float range = 40.f; // gltf No default, but blender default is 40
    PointLight() = default;
    PointLight(const json& j);
};
void to_json(json& j, const PointLight& l);

#endif