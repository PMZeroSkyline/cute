#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "motion.h"
#include "collider.h"

struct RigidBody
{
    std::shared_ptr<Motion> motion;
    std::shared_ptr<Collider> collider;

    std::shared_ptr<btRigidBody> bullet_body;

    RigidBody(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials, const vec3& local_scale);
    ~RigidBody();
};

#endif