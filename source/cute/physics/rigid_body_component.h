#ifndef RIGID_BODY_COMPONENT_H
#define RIGID_BODY_COMPONENT_H

#include "rigid_body.h"

struct RigidBodyComponent : Component
{
    std::shared_ptr<RigidBody> body;
    static inline std::vector<RigidBodyComponent*> components;
    RigidBodyComponent(std::shared_ptr<RigidBody> _body);
    ~RigidBodyComponent();
};

#endif