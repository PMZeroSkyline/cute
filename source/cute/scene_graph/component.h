#ifndef COMPONENT_H
#define COMPONENT_H

struct Node;
struct Component
{
    Node *owner = nullptr;
    virtual ~Component() = default;
    virtual void Update() {}
};

#endif