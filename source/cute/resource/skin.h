#ifndef SKIN_H
#define SKIN_H

#include "core/parser/json.h"
#include "scene_graph/node.h"

struct Skin
{
    std::string name;
    std::vector<mat4> inverse_bind_matrices;
    Node* skeleton = nullptr;
    std::vector<Node*> joints;
    Skin() = default;
    Skin(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Node>>& nodes);
    void get_matrices(std::vector<mat4>& matrices);
};

#endif