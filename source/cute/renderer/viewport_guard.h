#ifndef VIEWPORT_STASH_H
#define VIEWPORT_STASH_H
#include "platform/graphics_wrapper/gl_validation.h"
struct ViewportGuard
{
    GLint viewport[4];
    ViewportGuard();
    ~ViewportGuard();
};

#endif