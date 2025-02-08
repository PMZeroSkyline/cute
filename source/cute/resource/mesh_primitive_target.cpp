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
void MeshPrimitiveTarget::read_position(char *buf, int stride, int pointer, float weight) const
{
    if (!POSITION.size())
    {
        return;
    }
    if (position_indices.size())
    {
        for (int j = 0; j < position_indices.size(); j++)
        {
            unsigned int id = position_indices[j];
            *(vec3*)(buf + stride * id + pointer) += POSITION[j] * weight;
        }
    }
    else
    {
        for (int j = 0; j < POSITION.size(); j++)
        {
            *(vec3*)(buf + stride * j + pointer) += POSITION[j] * weight;
        }
    }
}
void MeshPrimitiveTarget::read_normal(char *buf, int stride, int pointer, float weight) const
{
    if (!NORMAL.size())
    {
        return;
    }
    if (normal_indices.size())
    {
        for (int j = 0; j < normal_indices.size(); j++)
        {
            unsigned int id = normal_indices[j];
            *(vec3*)(buf + stride * id + pointer) += NORMAL[j] * weight;
        }
    }
    else
    {
        for (int j = 0; j < NORMAL.size(); j++)
        {
            *(vec3*)(buf + stride * j + pointer) += NORMAL[j] * weight;
        }
    }
}
void MeshPrimitiveTarget::read_tangent(char *buf, int stride, int pointer, float weight) const
{
    if (!TANGENT.size())
    {
        return;
    }
    if (tangent_indices.size())
    {
        for (int j = 0; j < tangent_indices.size(); j++)
        {
            unsigned int id = tangent_indices[j];
            *(vec4*)(buf + stride * id + pointer) += TANGENT[j] * weight;
        }
    }
    else
    {
        for (int j = 0; j < TANGENT.size(); j++)
        {
            *(vec4*)(buf + stride * j + pointer) += TANGENT[j] * weight;
        }
    }
}