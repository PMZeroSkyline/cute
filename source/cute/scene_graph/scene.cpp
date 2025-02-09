#include "scene.h"
#include <unordered_set>
#include "physics/rigid_body_component.h"
#include "physics/physics_engine.h"
#include "device/app.h"

Scene::Scene(const json& j, const std::vector<std::shared_ptr<Node>>& _nodes)
{
    if (j.contains("nodes"))
    {
        for (auto& node : j["nodes"])
        {
            nodes.push_back(_nodes[node]);
            nodes.back()->update_world_matrices();
        }
    }
    if (j.contains("name"))
    {
        name = j["name"];
    }
}
void Scene::union_nodes(std::vector<std::shared_ptr<Node>>& _nodes)
{
    nodes.insert(nodes.end(), _nodes.begin(), _nodes.end());
    std::for_each(_nodes.begin(), _nodes.end(), [this](std::shared_ptr<Node>& n){
        n->scene = this;
    });
}
void Scene::except_nodes(std::vector<std::shared_ptr<Node>>& _nodes)
{
    std::unordered_set<std::shared_ptr<Node>> s_node(_nodes.begin(), _nodes.end());
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(), [&s_node](const std::shared_ptr<Node>& n) {
        return s_node.find(n) != s_node.end();
    }), nodes.end());
    std::for_each(_nodes.begin(), _nodes.end(), [](std::shared_ptr<Node>& n){
        n->scene = nullptr;
    });
}
void Scene::add_node(std::shared_ptr<Node> node)
{
    nodes.push_back(node);
    node->scene = this;
}
bool Scene::remove_node(Node* node)
{
    auto it = std::find(nodes.begin(), nodes.end(), [&node](const std::shared_ptr<Node>& nodes_item){
        nodes_item.get() == node;
    });
    if (it != nodes.end()) 
    {
        (*it)->scene = nullptr;
        nodes.erase(it);
        return true;
    }
    return false;
}
template<typename Func>
void Scene::walk_tree(const Func& func)
{
    for (const auto& n : nodes) 
    {
        n->walk_tree(func);
    }
}
Node* Scene::breadth_first_search(const std::string& target)
{
    std::queue<Node*> q;
    for (const auto& n : nodes)
    {
        q.push(n.get());
    }
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current->name == target) 
        {
            return current;
        }
        for (const auto& child : current->children) {
            q.push(child.get());
        }
    }
    return nullptr;
}
const Node* Scene::breadth_first_search(const std::string& target) const
{
    std::queue<const Node*> q;
    for (const auto& n : nodes)
    {
        q.push(n.get());
    }
    while (!q.empty()) {
        const Node* current = q.front();
        q.pop();
        if (current->name == target) 
        {
            return current;
        }
        for (const auto& child : current->children) {
            q.push(child.get());
        }
    }
    return nullptr;
}
bool Scene::remove(const std::string& target)
{
    if (Node* n = breadth_first_search(target))
    {
        return n->remove();
    }
    return false;
}
void Scene::update()
{
    for (int i = nodes.size() - 1; i >= 0; --i) 
    {
        nodes[i]->update();
    }
    for (const auto& comp : RigidBodyComponent::components)
    {
        comp->body->bullet_body->setWorldTransform(btTransform(comp->owner->get_world_rotation().bullet(), vec3(comp->owner->world_matrix.col(3)).bullet()));
    }
    PhysicsEngine::instance->dynamics_world->stepSimulation(App::instance->delta_time, 10);
    for (const auto& comp : RigidBodyComponent::components)
    {
        const btTransform& bTransform = comp->body->bullet_body->getWorldTransform();
        comp->owner->set_world_position(*(vec3*)&bTransform.getOrigin());
        comp->owner->set_world_rotation(quat(bTransform.getRotation()));
        comp->owner->update_world_matrices();
    }
}
bool Node::remove()
{
    if (parent)
    {
        return parent->remove_child(this);
    }
    else if (scene)
    {
        return scene->remove_node(this);
    }
    return false;
}