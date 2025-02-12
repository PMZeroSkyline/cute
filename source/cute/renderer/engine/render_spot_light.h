#ifndef RENDER_SPOT_LIGHT_H
#define RENDER_SPOT_LIGHT_H

#include "renderer/spot_light.h"
#include "scene_graph/node.h"
struct RenderSpotLight
{
    Node* node = nullptr;
    SpotLight* light = nullptr;
};


#endif