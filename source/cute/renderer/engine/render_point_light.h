#ifndef RENDER_POINT_LIGHT_H
#define RENDER_POINT_LIGHT_H

#include "renderer/point_light.h"
#include "scene_graph/node.h"
struct RenderPointLight
{
    Node* node = nullptr;
    PointLight* light = nullptr;
};


#endif