#include "mesh_primitive_attributes.h"
#include <iostream>
#include "gltf_access.h"

MeshPrimitiveAttributes::MeshPrimitiveAttributes(const json& j, const json& gltf, const std::string& dir)
{
    if (j.contains("POSITION"))
    {
        json accessor = gltf["accessors"][int(j["POSITION"])];
        if (!gltf_access(dir, gltf, accessor, &POSITION, nullptr))
            std::cout << "failed to read mesh" << std::endl;
        bbox = AABB::make(accessor["min"], accessor["max"]);;
    }
    if (j.contains("NORMAL"))
    {
        json accessor = gltf["accessors"][int(j["NORMAL"])];
        if (!gltf_access(dir, gltf, accessor, &NORMAL, nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("TANGENT"))
    {
        json accessor = gltf["accessors"][int(j["TANGENT"])];
        if (!gltf_access(dir, gltf, accessor, &TANGENT, nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("TEXCOORD_0"))
    {
        json accessor = gltf["accessors"][int(j["TEXCOORD_0"])];
        if (!gltf_access(dir, gltf, accessor, &TEXCOORD_0, nullptr))
            std::cout << "failed to read mesh" << std::endl;
        for (auto& uv : TEXCOORD_0) {
            uv.y = 1.f - uv.y;
        }
    }
    if (j.contains("TEXCOORD_1"))
    {
        json accessor = gltf["accessors"][int(j["TEXCOORD_1"])];
        if (!gltf_access(dir, gltf, accessor, &TEXCOORD_1, nullptr))
            std::cout << "failed to read mesh" << std::endl;
        for (auto& uv : TEXCOORD_1) {
            uv.y = 1.f - uv.y;
        }
    }
    if (j.contains("TEXCOORD_2"))
    {
        json accessor = gltf["accessors"][int(j["TEXCOORD_2"])];
        if (!gltf_access(dir, gltf, accessor, &TEXCOORD_2, nullptr))
            std::cout << "failed to read mesh" << std::endl;
        for (auto& uv : TEXCOORD_2) {
            uv.y = 1.f - uv.y;
        }
    }
    if (j.contains("TEXCOORD_3"))
    {
        json accessor = gltf["accessors"][int(j["TEXCOORD_3"])];
        if (!gltf_access(dir, gltf, accessor, &TEXCOORD_3, nullptr))
            std::cout << "failed to read mesh" << std::endl;
        for (auto& uv : TEXCOORD_3) {
            uv.y = 1.f - uv.y;
        }
    }
    if (j.contains("COLOR_0"))
    {
        json accessor = gltf["accessors"][int(j["COLOR_0"])];
        if (!gltf_access(dir, gltf, accessor, &COLOR_0, nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("JOINTS_0"))
    {
        json accessor = gltf["accessors"][int(j["JOINTS_0"])];
        if (!gltf_access(dir, gltf, accessor, &JOINTS_0, nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("WEIGHTS_0"))
    {
        json accessor = gltf["accessors"][int(j["WEIGHTS_0"])];
        if (!gltf_access(dir, gltf, accessor, &WEIGHTS_0, nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
}