#include "renderbuffer.h"

Renderbuffer::Renderbuffer()
{
    glGenRenderbuffers(1, &id);
}
Renderbuffer::Renderbuffer(GLsizei _width, GLsizei _height, GLenum _internalformat, GLsizei _samples) : width(_width), height(_height), internalformat(_internalformat), samples(_samples)
{
    glGenRenderbuffers(1, &id);
    bind();
    storage();
}
Renderbuffer::~Renderbuffer()
{
    glDeleteRenderbuffers(1, &id);
}
void Renderbuffer::bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}
void Renderbuffer::storage()
{
    if (samples)
    {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
    }
    else
    {
        glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
    }
}