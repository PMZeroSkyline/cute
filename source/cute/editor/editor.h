#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H
#include <memory>
struct Editor
{
    static inline std::shared_ptr<Editor> instance = nullptr;
    Editor();
    void render();
};

#endif