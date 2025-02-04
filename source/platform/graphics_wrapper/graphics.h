#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <memory>
#include "graphics_api.h"
#include "opengl/opengl_api.h"

struct Graphics
{
    static inline std::shared_ptr<GraphicsAPI> api;
};

#endif