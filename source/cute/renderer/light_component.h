#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "scene_graph/component.h"
#include "light.h"
struct LightComponent : Component
{
    std::shared_ptr<Light> light;
    LightComponent() = default;
    LightComponent(const std::shared_ptr<Light>& _light);
};

#endif