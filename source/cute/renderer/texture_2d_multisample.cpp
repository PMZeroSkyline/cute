#include "texture_2d_multisample.h"

Texture2DMultisample::Texture2DMultisample(GLsizei _width, GLsizei _height, GLint _internalformat, GLsizei _samples, GLboolean _fixedsamplelocations) : samples(_samples), width(_width), height(_height), fixedsamplelocations(_fixedsamplelocations), Texture("", nullptr, _internalformat, 0)
{
    bind();
    tex_image();
}
GLenum Texture2DMultisample::get_target()
{
    return GL_TEXTURE_2D_MULTISAMPLE;
}
void Texture2DMultisample::tex_image()
{
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalformat, width, height, fixedsamplelocations);
}