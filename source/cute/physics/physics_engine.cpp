#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
    collision_configuration = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(collision_configuration.get());
    overlapping_pair_cache = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    dynamics_world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), overlapping_pair_cache.get(), solver.get(), collision_configuration.get());
    dynamics_world->setGravity(btVector3(0, 0, -10.0));
}
PhysicsEngine::~PhysicsEngine()
{
    dynamics_world.release();
    solver.release();
    overlapping_pair_cache.release();
    dispatcher.release();
    collision_configuration.release();
}