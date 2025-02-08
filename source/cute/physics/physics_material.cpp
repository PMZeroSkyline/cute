#include "physics_material.h"

PhysicsMaterial::PhysicsMaterial(const json& j)
{
    restitution = j["restitution"];
    static_friction = j["staticFriction"];
    dynamic_friction = j["dynamicFriction"];
}