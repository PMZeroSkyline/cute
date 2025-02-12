#include "uniform_camera_block.h"

UniformCameraBlock::UniformCameraBlock()
{
    buffer = Buffer::get_uniform<std140::CameraBlock>("CameraBlock");
}
void UniformCameraBlock::submit(const vec3& camera_pos, float znear, float zfar, const mat4& V, const mat4& P)
{
    std140::CameraBlock block = {V, P, camera_pos, znear, zfar};
    buffer->bind();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(std140::CameraBlock), &block);
}