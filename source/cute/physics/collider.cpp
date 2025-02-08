#include "collider.h"

Collider::Collider(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials, const vec3& local_scale)
{
    geometry = std::make_shared<Geometry>(j["geometry"], shapes, nodes, local_scale);
    physics_material = physics_materials[j["physicsMaterial"]];
}