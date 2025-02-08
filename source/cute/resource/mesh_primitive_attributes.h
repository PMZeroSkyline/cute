#ifndef MESH_PRIMITIVE_ATTRIBUTES_H
#define MESH_PRIMITIVE_ATTRIBUTES_H

#include "core/parser/json.h"
#include "core/math/aabb.h"

struct MeshPrimitiveAttributes
{
    std::vector<vec3> POSITION;
    std::vector<vec3> NORMAL;
    std::vector<vec4> TANGENT;
    std::vector<vec2> TEXCOORD_0;
    std::vector<vec2> TEXCOORD_1;
    std::vector<vec2> TEXCOORD_2;
    std::vector<vec2> TEXCOORD_3;
    std::vector<vec3> COLOR_0;
    std::vector<vec4> JOINTS_0;
    std::vector<vec4> WEIGHTS_0;
    std::shared_ptr<AABB> bbox;
    MeshPrimitiveAttributes() = default;
    MeshPrimitiveAttributes(const json& j, const json& gltf, const std::string& dir);
};

#endif