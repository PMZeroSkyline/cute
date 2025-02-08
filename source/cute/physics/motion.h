#ifndef MOTION_H
#define MOTION_H
#include "core/parser/json.h"
#include "core/math/vec3.h"
struct Motion
{
    bool is_kinematic = false;
    float mass = 0.f;
    vec3 center_of_mass;
    vec3 linear_velocity;
    vec3 angular_velocity;
    vec3 inertia_diagonal = vec3(-1.f);

    Motion() = default;
    Motion(const json& j);
};

#endif