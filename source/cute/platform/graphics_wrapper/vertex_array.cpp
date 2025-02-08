#include "vertex_array.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}
void VertexArray::bind() const
{
    glBindVertexArray(id);
}