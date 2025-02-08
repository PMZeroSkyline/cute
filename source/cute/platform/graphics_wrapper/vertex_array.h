#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "platform/graphics_wrapper/gl_validation.h"

struct VertexArray
{
    GLuint id = -1;
    VertexArray();
    virtual ~VertexArray();
    void bind() const;
};

#endif