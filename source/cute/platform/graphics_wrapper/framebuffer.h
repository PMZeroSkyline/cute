#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "platform/graphics_wrapper/gl_validation.h"
#include <unordered_map>
#include <memory>
#include <string>

struct Framebuffer
{    
    GLuint id = -1;
    Framebuffer();
    ~Framebuffer();
    void bind();
    static void bind_default();
    static GLint get_binding();
    static inline std::unordered_map<std::string, std::shared_ptr<Framebuffer>> sharedMap;
};

#endif