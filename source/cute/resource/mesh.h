#ifndef MESH_H
#define MESH_H
#include "mesh_primitive.h"
struct Mesh
{
    std::vector<std::shared_ptr<MeshPrimitive>> primitives;
    std::string name;
    std::vector<float> weights;
    std::shared_ptr<AABB> bbox;
    Mesh() = default;
    Mesh(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Material>>& materials);
    void update();
};
#endif