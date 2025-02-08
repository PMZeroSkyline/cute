#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H

#include <memory>

struct GraphicsAPI
{
    virtual ~GraphicsAPI() = default;
    static inline std::shared_ptr<GraphicsAPI> instance = nullptr;
    virtual void swap_buffers() = 0;
};

#endif