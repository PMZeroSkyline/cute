#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <memory>
struct RenderEngine
{
    static inline std::shared_ptr<RenderEngine> instance = nullptr;
    RenderEngine();
    void render();
};

#endif