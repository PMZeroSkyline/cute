#ifndef UNIFORM_LIGHT_BLOCK_H
#define UNIFORM_LIGHT_BLOCK_H

#include "platform/graphics_wrapper/buffer.h"
#include "layout_camera_block.h"

struct UniformLightBlock
{
    std::shared_ptr<Buffer> buffer;
    static inline std::shared_ptr<UniformLightBlock> instance = nullptr;
    UniformLightBlock();
    void submit(const vec3& camera_pos, float znear, float zfar, const mat4& V, const mat4& P);
};
#endif