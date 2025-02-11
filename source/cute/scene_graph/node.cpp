#include "node.h"

Node::Node(const json& j)
{
    if (j.contains("matrix"))
    {
        mat4 matrix = j["matrix"];
        local_transform = Transform(matrix);
    }
    if (j.contains("rotation"))
    {
        local_transform.rotation = j["rotation"];
    }
    if (j.contains("scale"))
    {
        local_transform.scale = j["scale"];
    }
    if (j.contains("translation"))
    {
        local_transform.position = j["translation"];
    }
    if (j.contains("name"))
    {
        name = j["name"];
    }
}
void Node::update()
{
    for (auto& c : components)
    {
        c->Update();
    }
    for (auto& c : children)
    {
        c->update();
    }
}
bool Node::remove_child(Node* node)
{
    std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(children.begin(), children.end(), [&node](const std::shared_ptr<Node>& val){
        return node == val.get();
    });
    if (it != children.end()) 
    {
        children.erase(it);
        return true;
    }
    return false;
}
quat Node::get_world_rotation() const
{
    return parent ? parent->get_world_rotation() * local_transform.rotation : local_transform.rotation;
}
vec3 Node::get_world_scale() const
{
    return parent ? parent->get_world_scale() * local_transform.scale : local_transform.scale;
}
void Node::set_world_position(const vec3 &pos)
{
    world_matrix(0, 3) = pos.x;
    world_matrix(1, 3) = pos.y;
    world_matrix(2, 3) = pos.z;
    local_transform.position = (parent ? inverse(parent->world_matrix) * world_matrix : world_matrix).col(3);
}
void Node::set_world_rotation(const quat &rot)
{
    local_transform.rotation = parent ? inverse(parent->get_world_rotation()) * rot : rot;
}
void Node::set_world_scale(const vec3 &scal)
{
    local_transform.scale = parent ? scal / parent->get_world_scale() : scal;
}
void Node::update_world_matrices()
{
    world_matrix = parent ? parent->world_matrix * local_transform.to_matrix() : local_transform.to_matrix(); 
    for (const std::shared_ptr<Node>& child : children) 
    {
        child->update_world_matrices();
    }
}
const Node* Node::search(const std::string& target) const
{
    if (name == target) 
    {
        return this;
    }
    for (const std::shared_ptr<Node>& child : children) 
    {
        if (const Node* n = child->search(target)) 
        {
            return n;
        }
    }
    return nullptr;
}
Node* Node::search(const std::string& target)
{
    if (name == target) 
    {
        return this;
    }
    for (const std::shared_ptr<Node>& child : children) 
    {
        if (Node* n = child->search(target)) 
        {
            return n;
        }
    }
    return nullptr;
}
const Node* Node::breadth_first_search(const std::string& target) const
{
    std::queue<const Node*> q;
    q.push(this);
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
Node* Node::breadth_first_search(const std::string& target)
{
    std::queue<Node*> q;
    q.push(this);
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
std::shared_ptr<Node> make_tree(int depth, int breadth, int currentDepth, int currentIndex) 
{
    std::shared_ptr<Node> node = std::make_shared<Node>(std::to_string(currentDepth) + "_" + std::to_string(currentIndex));
    if (depth == 0) 
    {
        return node;
    }
    for (int i = 0; i < breadth; ++i) 
    {
        node->add_child(make_tree(depth - 1, breadth, currentDepth + 1, i));
    }
    return node;
}
void node_out(std::ostream& os, const Node& node, const std::string& prefix, bool isLast) 
{
    os << prefix;
    if (isLast) {
        os << "+-- ";
    } else {
        os << "|-- ";
    }
    os << node.name << std::endl;
    for (size_t i = 0; i < node.children.size(); ++i) 
    {
        node_out(os, *node.children[i], prefix + (isLast ? "    " : "|   "), i == node.children.size() - 1);
    }
}
std::ostream& operator<<(std::ostream& os, const Node& node) 
{
    node_out(os, node, "", true);
    return os;
}
void to_json(json& j, const Node& n)
{
    if (n.local_transform.position != vec3())
    {
        j["translation"] = n.local_transform.position;
    }
    if (n.local_transform.position != vec3(1.f))
    {
        j["scale"] = n.local_transform.scale;
    }
    if (n.local_transform.rotation != quat())
    {
        j["rotation"] = n.local_transform.rotation;
    }
    if (n.name != "")
    {
        j["name"] = n.name;
    }
}