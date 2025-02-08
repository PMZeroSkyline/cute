#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "platform/graphics_wrapper/gl/gl_validation.h"

struct Renderbuffer
{
    GLuint id = -1;
    GLenum internalformat;
    GLsizei width;
    GLsizei height;
    GLsizei samples;
    Renderbuffer();
    Renderbuffer(GLsizei _width, GLsizei _height, GLenum _internalformat, GLsizei _samples = 0);
    ~Renderbuffer();
    void bind();
    void storage();
};

#endif