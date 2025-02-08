#include "mesh_primitive_target.h"

MeshPrimitiveTarget::MeshPrimitiveTarget(const json &j, const json& gltf, const std::string &dir)
{
    if (j.contains("POSITION"))
    {
        json accessor = gltf["accessors"][int(j["POSITION"])];
        if (!gltf_access(dir, gltf, accessor, &POSITION, &position_indices))
            std::cout << "failed to read mesh" << std::endl;
        bbox = AABB::make(accessor["min"], accessor["max"]);
    }
    if (j.contains("NORMAL"))
    {
        json accessor = gltf["accessors"][int(j["NORMAL"])];
        if (!gltf_access(dir, gltf, accessor, &NORMAL, &normal_indices))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("TANGENT"))
    {
        json accessor = gltf["accessors"][j["TANGENT"]];
        if (!gltf_access(dir, gltf, accessor, &TANGENT, &tangent_indices))
            std::cout << "failed to read mesh" << std::endl;
    }
}