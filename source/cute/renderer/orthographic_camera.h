#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

struct OrthographicCamera : Camera
{
    float xmag = 5.f;
    float ymag = 5.f;

    OrthographicCamera(const json& j);
    mat4 get_projection() const override;
};

#endif