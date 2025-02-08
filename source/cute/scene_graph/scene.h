#ifndef SCENE_H
#define SCENE_H

#include "node.h"

struct Scene
{
    std::string name;
    std::vector<std::shared_ptr<Node>> nodes;
    Scene() = default;
    Scene(const json& j, const std::vector<std::shared_ptr<Node>>& _nodes);
    void union_nodes(std::vector<std::shared_ptr<Node>>& _nodes);
    void except_nodes(std::vector<std::shared_ptr<Node>>& _nodes);
    void add_node(std::shared_ptr<Node> node);
    bool remove_node(std::shared_ptr<Node> node);
    template<typename Func>
    void walk_tree(const Func& func);
    Node* breadth_first_search(const std::string& target);
    const Node* breadth_first_search(const std::string& target) const;
    bool remove(const std::string& target);
    void update();
};

#endif