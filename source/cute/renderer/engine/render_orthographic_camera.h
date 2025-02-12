#ifndef RENDER_ORTHOGRAPHIC_LIGHT_H
#define RENDER_ORTHOGRAPHIC_LIGHT_H

#include "renderer/orthographic_camera.h"
#include "scene_graph/node.h"
struct RenderOrthographicCamera
{
    Node* node = nullptr;
    OrthographicCamera* camera = nullptr;
};


#endif