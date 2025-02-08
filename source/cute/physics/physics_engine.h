#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "platform/physics_wrapper.h"
#include <memory>

struct PhysicsEngine
{
    std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration;
	std::unique_ptr<btCollisionDispatcher> dispatcher;
	std::unique_ptr<btBroadphaseInterface> overlapping_pair_cache;
	std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
	std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world;
    PhysicsEngine();
    ~PhysicsEngine();
    static inline std::shared_ptr<PhysicsEngine> instance = std::make_shared<PhysicsEngine>();
};

#endif