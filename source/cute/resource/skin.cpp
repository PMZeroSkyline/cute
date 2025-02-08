#include "skin.h"
#include "gltf_access.h"
#include <iostream>
Skin::Skin(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Node>>& nodes)
{
    if (j.contains("inverseBindMatrices"))
    {
        json accessor = gltf["accessors"][int(j["inverseBindMatrices"])];
        if (!gltf_access(dir, gltf, accessor, &inverse_bind_matrices, nullptr))
            std::cout << "failed to read skin" << std::endl;
    }
    if (j.contains("skeleton"))
    {
        skeleton = nodes[int(j["skeleton"])].get();
    }
    for (auto& joint : j["joints"])
    {
        joints.push_back(nodes[joint].get());
    }
    if (j.contains("name"))
    {
        name = j["name"];
    }
}
void Skin::get_matrices(std::vector<mat4>& matrices)
{
    matrices.reserve(joints.size());
    for (int i = 0; i < joints.size(); i++) {
        matrices.push_back(joints[i]->world_matrix * inverse_bind_matrices[i]);
    }
}