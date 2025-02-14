#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include <memory>
#include <vector>
#include "render_object.h"
#include "renderer/camera_component.h"
#include "renderer/light_component.h"
struct RenderWorld
{
    std::vector<RenderObject> render_objects;
    std::vector<CameraComponent*> perspective_camera_components;
    std::vector<CameraComponent*> orthographic_camera_components;
    std::vector<LightComponent*> directional_light_components;
    std::vector<LightComponent*> point_light_components;
    std::vector<LightComponent*> spot_light_components;
    std::vector<LightComponent*> image_based_light_components;
    static inline std::shared_ptr<RenderWorld> instance = nullptr;
    RenderWorld();
    void update();
};

#endif