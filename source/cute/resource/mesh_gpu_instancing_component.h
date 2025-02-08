#ifndef MESH_GPU_INSTANCING_COMPONENT_H
#define MESH_GPU_INSTANCING_COMPONENT_H

#include "mesh_gpu_instancing.h"
#include "scene_graph/component.h"
struct MeshGPUInstancingComponent : Component
{
    std::shared_ptr<MeshGPUInstancing> mesh_gpu_instancing;
    MeshGPUInstancingComponent(const std::shared_ptr<MeshGPUInstancing>& _mesh_gpu_instancing);
};

#endif