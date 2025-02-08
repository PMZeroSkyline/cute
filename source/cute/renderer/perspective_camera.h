#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

struct PerspectiveCamera : Camera
{
    float aspect_ratio = 1.f;
    float yfov = radians(60.f);
    PerspectiveCamera() = default;
    PerspectiveCamera(float _aspectRatio, float _yfov = radians(60.f), float _znear = .1f, float _zfar = 1000.f);
    PerspectiveCamera(const json& j);
    mat4 get_projection() const override;
};

#endif