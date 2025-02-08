#ifndef TEXTURE_2D_MULTISAMPLE_H
#define TEXTURE_2D_MULTISAMPLE_H
#include "texture.h"
#include "platform/graphics_wrapper/gl_validation.h"
struct Texture2DMultisample : Texture
{   
    GLsizei samples;
    GLsizei width;
    GLsizei height;
    GLboolean fixedsamplelocations;
    Texture2DMultisample() = default;
    Texture2DMultisample(GLsizei _width, GLsizei _height, GLint _internalformat, GLsizei _samples = 4, GLboolean _fixedsamplelocations = GL_TRUE);
    GLenum get_target() override;
    void submit();
};
#endif