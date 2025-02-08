#include "rigid_body.h"
#include "physics_engine.h"

RigidBody::RigidBody(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials, const vec3& local_scale)
{
    collider = std::make_shared<Collider>(j["collider"], shapes, nodes, physics_materials, local_scale);
    if (j.contains("motion"))
    {
        motion = std::make_shared<Motion>(j["motion"]);
    }
    else
    {
        motion = std::make_shared<Motion>();
    }
    btVector3 localInertia(0, 0, 0);
    if (motion->inertia_diagonal != vec3(-1.f))
    {
        localInertia = *(btVector3*)&motion->inertia_diagonal;   
    }
    else if (motion->mass != 0.f)
    {
        collider->geometry->shape->bullet_shape->calculateLocalInertia(motion->mass, localInertia);
    }
    btRigidBody::btRigidBodyConstructionInfo rbInfo(motion->mass, nullptr, collider->geometry->shape->bullet_shape.get(), localInertia);
    bullet_body = std::make_shared<btRigidBody>(rbInfo);
    if (motion->is_kinematic)
    {
        bullet_body->setCollisionFlags(bullet_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    PhysicsEngine::instance->dynamics_world->addRigidBody(bullet_body.get());
}
RigidBody::~RigidBody()
{
    if (PhysicsEngine::instance->dynamics_world)
    {
        PhysicsEngine::instance->dynamics_world->removeRigidBody(bullet_body.get());
    }
}