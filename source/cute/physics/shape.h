#ifndef SHAPE_H
#define SHAPE_H

#include "platform/physics_wrapper.h"
#include <memory>

struct Shape
{
    std::shared_ptr<btCollisionShape> bullet_shape;
    virtual ~Shape();
};

#endif