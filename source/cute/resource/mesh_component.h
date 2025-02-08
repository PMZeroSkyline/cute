#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "scene_graph/component.h"
#include "mesh.h"

struct MeshComponent : Component
{
    std::shared_ptr<Mesh> mesh;
    MeshComponent();
    MeshComponent(const std::shared_ptr<Mesh>& _mesh);
};

#endif