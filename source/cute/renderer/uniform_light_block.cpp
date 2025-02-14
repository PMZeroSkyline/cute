#include "uniform_light_block.h"

UniformLightBlock::UniformLightBlock()
{
    buffer = Buffer::get_uniform<std140::CameraBlock>("LightBlock");
}
void UniformLightBlock::submit(const vec3& camera_pos, float znear, float zfar, const mat4& V, const mat4& P)
{
    std140::CameraBlock block = {V, P, camera_pos, znear, zfar};
    buffer->bind();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(std140::CameraBlock), &block);
}