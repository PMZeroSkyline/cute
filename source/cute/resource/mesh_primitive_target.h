#ifndef MESH_PRIMITIVE_TARGET_H
#define MESH_PRIMITIVE_TARGET_H

#include "gltf_access.h"
#include "core/math/aabb.h"

struct MeshPrimitiveTarget
{
    std::vector<vec3> POSITION;
    std::vector<vec3> NORMAL;
    std::vector<vec4> TANGENT;
    std::vector<unsigned int> position_indices;
    std::vector<unsigned int> normal_indices;
    std::vector<unsigned int> tangent_indices;
    std::shared_ptr<AABB> bbox;
    MeshPrimitiveTarget() = default;
    MeshPrimitiveTarget(const json &j, const json& gltf, const std::string &dir);
};

#endif