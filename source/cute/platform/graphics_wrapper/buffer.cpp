#include "buffer.h"

Buffer::Buffer(GLenum _target) : target(_target)
{
    glGenBuffers(1, &id);
}
Buffer::~Buffer()
{
    glDeleteBuffers(1, &id);
}
void Buffer::bind()
{
    glBindBuffer(target, id);
}