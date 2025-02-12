#ifndef UNIFORM_CAMERA_BLOCK_H
#define UNIFORM_CAMERA_BLOCK_H

#include "platform/graphics_wrapper/buffer.h"
#include "std140_camera_block.h"

struct UniformCameraBlock
{
    std::shared_ptr<Buffer> buffer;
    static inline std::shared_ptr<UniformCameraBlock> instance = nullptr;
    UniformCameraBlock();
    void submit(const vec3& cameraPos, float znear, float zfar, const mat4& V, const mat4& P);
};
#endif