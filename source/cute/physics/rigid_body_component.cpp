#include "rigid_body_component.h"

RigidBodyComponent::RigidBodyComponent(std::shared_ptr<RigidBody> _body) : body(_body)
{
    components.push_back(this);
}
RigidBodyComponent::~RigidBodyComponent()
{
    auto it = std::find(components.begin(), components.end(), this);
    if (it != components.end()) 
    {
        components.erase(it);
    }
}