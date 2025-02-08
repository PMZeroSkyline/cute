#ifndef PHYSICS_MATERIAL_H
#define PHYSICS_MATERIAL_H

#include "core/parser/json.h"

struct PhysicsMaterial
{
    float restitution;
    float static_friction;
    float dynamic_friction;
    PhysicsMaterial(const json& j);
};

#endif