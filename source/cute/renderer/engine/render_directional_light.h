#ifndef RENDER_DIRECTIONAL_LIGHT_H
#define RENDER_DIRECTIONAL_LIGHT_H

#include "renderer/directional_light.h"
#include "scene_graph/node.h"
struct RenderDirectionalLight
{
    Node* node = nullptr;
    DirectionalLight* light = nullptr;
};


#endif