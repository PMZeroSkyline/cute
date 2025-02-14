#ifndef CAMERA_BLOCK_GLSL
#define CAMERA_BLOCK_GLSL
layout (std140) uniform CameraBlock
{
    mat4 iV;
    mat4 iP;
    vec3 iCameraPosition;
    float iZNear;
    float iZFar;
};
#endif