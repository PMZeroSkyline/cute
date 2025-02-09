#ifndef VIEWPORT_STASH_H
#define VIEWPORT_STASH_H
#include "platform/graphics_wrapper/gl_validation.h"
struct ViewportStash
{
    GLint viewport[4];
    ViewportStash();
    ~ViewportStash();
};

#endif