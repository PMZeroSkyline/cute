#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include <memory>
#include <vector>
#include "render_point_light.h"
#include "render_spot_light.h"
#include "render_directional_light.h"
#include "render_object.h"
#include "render_perspective_camera.h"
#include "render_orthographic_camera.h"
#include "renderer/image_based_light.h"

struct RenderWorld
{
    std::vector<RenderObject> render_objects;
    std::vector<RenderPerspectiveCamera> perspective_cameras;
    std::vector<RenderOrthographicCamera> orthographic_cameras;
    std::vector<RenderPointLight> point_lights;
    std::vector<RenderSpotLight> spot_lights;
    std::vector<RenderDirectionalLight> directional_lights;
    std::vector<ImageBasedLight*> image_based_lights;
    static inline std::shared_ptr<RenderWorld> instance = nullptr;
    RenderWorld();
    void update();
};

#endif