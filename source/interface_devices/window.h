#ifndef WINDOW_H
#define WINDOW_H

#include "core/math/vec2.h"

struct Window
{
    ivec2 size;
    ivec2 render_size;

    virtual bool is_open() const = 0;
    virtual void reset_input() = 0;
};


#endif