#include "mesh_component.h"

MeshComponent::MeshComponent()
{
    mesh = std::make_shared<Mesh>();
}
MeshComponent::MeshComponent(const std::shared_ptr<Mesh>& _mesh) : mesh(_mesh){}