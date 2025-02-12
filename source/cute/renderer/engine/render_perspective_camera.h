#ifndef RENDER_PERSPECTIVE_LIGHT_H
#define RENDER_PERSPECTIVE_LIGHT_H

#include "renderer/perspective_camera.h"
#include "scene_graph/node.h"
struct RenderPerspectiveCamera
{
    Node* node = nullptr;
    PerspectiveCamera* camera = nullptr;
};


#endif