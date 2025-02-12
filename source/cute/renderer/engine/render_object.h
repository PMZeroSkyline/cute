#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "scene_graph/node.h"
#include "resource/mesh.h"
#include "resource/skin.h"
#include "resource/mesh_gpu_instancing.h"

struct RenderObject
{
    Node* node = nullptr;
    Mesh* mesh = nullptr;
    Skin* skin = nullptr;
    MeshGPUInstancing* mesh_gpu_instancing = nullptr;
    float distance_square;
};

#endif