#ifndef CURSOR_H
#define CURSOR_H

#include "core/math/vec2.h"

struct Cursor
{
    vec2 pos = vec2(FLT_MAX);
    vec2 dt_pos = vec2(0.f);
};

#endif