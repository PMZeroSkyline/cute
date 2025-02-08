#ifndef UNIFORM_CAMERA_BLOCK_H
#define UNIFORM_CAMERA_BLOCK_H

#include "core/math/mat4.h"

namespace std140
{
    struct CameraBlock
    {
        mat4 iV;
        mat4 iP;
        vec3 iCameraPosition;
        float iZNear;
        float iZFar;
    };
}
#endif