#ifndef HDR_LIGHTING_H
#define HDR_LIGHTING_H

#include "platform/graphics_wrapper/gl_validation.h"
#include "platform/graphics_wrapper/framebuffer.h"
#include "renderer/texture_2d.h"
#include "renderer/texture_cube.h"
#include "renderer/perspective_camera.h"
#include "renderer/viewport_stash.h"
#include "resource/material.h"
#include "resource/mesh_primitive.h"
struct ViewportStash
{
    GLint viewport[4];
    ViewportStash() 
    {
        glGetIntegerv(GL_VIEWPORT, viewport);
    }
    ~ViewportStash() 
    {
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    }
};
std::shared_ptr<TextureCube> hdr_cube(const std::string& hdr_path, int size);
#endif