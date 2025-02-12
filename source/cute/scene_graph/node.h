#ifndef NODE_H
#define NODE_H

#include <memory>
#include <queue>
#include <string>
#include "core/parser/json.h"
#include "component.h"
#include "transform.h"

struct Scene;
struct Node
{
    std::string name;
    Transform local_transform;
    mat4 world_matrix;
    Node* parent = nullptr;
    Scene* scene = nullptr;
    std::vector<std::shared_ptr<Node>> children;
    std::vector<std::shared_ptr<Component>> components;
    Node() = default;
    Node(const json& j);
    virtual ~Node() {} // make sure Derived destructor called when using Base pointer delete
    virtual void update();
    template <typename T>
    std::shared_ptr<T> add_child(std::shared_ptr<T> add)
    {
        children.push_back(add);
        ((Node *)add.get())->parent = this;
        return add;
    }
    template <typename T, typename... Args>
    std::shared_ptr<T> add_child(Args &&...args)
    {
        std::shared_ptr<T> add = std::make_shared<T>(std::forward<Args>(args)...);
        children.push_back(add);
        ((Node *)add.get())->parent = this;
        return add;
    }
    template <typename T>
    std::shared_ptr<T> add_component(std::shared_ptr<T> add)
    {
        components.push_back(add);
        ((Component *)add.get())->owner = this;
        return add;
    }
    template <typename T, typename... Args>
    std::shared_ptr<T> add_component(Args &&...args)
    {
        std::shared_ptr<T> add = std::make_shared<T>(std::forward<Args>(args)...);
        components.push_back(add);
        ((Component *)add.get())->owner = this;
        return add;
    }
    template <typename T>
    std::shared_ptr<T> get_component() const
    {
        for (int i = 0; i < components.size(); i++)
        {
            auto &r = *components[i].get();
            if (typeid(T) == typeid(r))
            {
                return std::dynamic_pointer_cast<T>(components[i]);
            }
        }
        return std::shared_ptr<T>();
    }
    template <typename T>
    bool remove_component()
    {
        for (int i = 0; i < components.size(); i++)
        {
            auto &r = *components[i].get();
            if (typeid(T) == typeid(r))
            {
                components.erase(components.begin() + i);
                return true;
            }
        }
        return false;
    }
    template <typename T>
    bool remove_component(const std::shared_ptr<T>& component)
    {
        auto it = std::find(components.begin(), components.end(), component);
        if (it != components.end())
        {
            components.erase(it);
            return true;
        }
        return false;
    }
    template<typename Func>
    void walk_tree(const Func& func) // DepthFirstTraversal. faster then BFT if target deeper
    {
        func(this);
        for (const std::shared_ptr<Node>& child : children) 
        {
            child->walk_tree(func);
        }
    }
    template<typename Func>
    bool walk_tree_if(const Func& func)
    {
        if (func(this)) {
            return true;
        }
        for (const std::shared_ptr<Node>& child : children) {
            if (child->walk_tree_if(func)) {
                return true;
            }
        }
        return false;
    }
    template<typename Func>
    void walk_tree_breadth(const Func& func) // BreadthFirstTraversal
    {
        std::queue<const Node*> q;
        q.push(this);

        while (!q.empty()) {
            const Node* current = q.front();
            q.pop();

            func(current);

            for (const auto& child : current->children) {
                q.push(child.get());
            }
        }
    }
    template<typename Func>
    void walk_tree_breadth_if(const Func& func)
    {
        std::queue<const Node*> q;
        q.push(this);

        while (!q.empty()) {
            const Node* current = q.front();
            q.pop();

            if (func(current))
            {
                break;
            }

            for (const auto& child : current->children) {
                q.push(child.get());
            }
        }
    }
    bool remove_child(Node* node);
    quat get_world_rotation() const;
    vec3 get_world_scale() const;
    void set_world_position(const vec3 &pos);
    void set_world_rotation(const quat &rot);
    void set_world_scale(const vec3 &scal);
    void update_world_matrices();
    const Node* search(const std::string& target) const;
    Node* search(const std::string& target);
    const Node* breadth_first_search(const std::string& target) const;
    Node* breadth_first_search(const std::string& target);
    bool remove();
};
std::shared_ptr<Node> make_tree(int depth, int breadth, int currentDepth = 0, int currentIndex = 0);
void node_out(std::ostream& os, const Node& node, const std::string& prefix = "", bool isLast = true);
std::ostream& operator<<(std::ostream& os, const Node& node);
void to_json(json& j, const Node& n);
#endif