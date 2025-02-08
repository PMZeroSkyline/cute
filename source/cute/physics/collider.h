#ifndef COLLIDER_H
#define COLLIDER_H

#include "geometry.h"
#include "physics_material.h"

struct Collider
{
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<PhysicsMaterial> physics_material;
    Collider(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials, const vec3& local_scale);
};

#endif