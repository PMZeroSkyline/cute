#include "framebuffer.h"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &id);
}
Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &id);
}
void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}
void Framebuffer::bind_default()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
GLint Framebuffer::get_binding()
{
    GLint binding;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &binding);
    return binding;
}