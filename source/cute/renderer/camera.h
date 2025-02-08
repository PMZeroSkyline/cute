#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "core/parser/json.h"
#include "core/math/mat4.h"

struct Camera
{
    std::string name;
    float znear = .1f;
    float zfar = 1000.f;

    Camera() = default;
    Camera(float _znear, float _far);
    Camera(const json& j);
    virtual mat4 get_projection() const = 0;
};

#endif