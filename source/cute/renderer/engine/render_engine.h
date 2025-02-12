#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <memory>
#include <vector>
#include "render_pass.h"
struct RenderEngine
{
    std::vector<std::shared_ptr<RenderPass>> passes;
    static inline std::shared_ptr<RenderEngine> instance = nullptr;
    RenderEngine();
    void render();
    template <typename T, typename... Args>
    std::shared_ptr<T> add_pass(Args &&...args)
    {
        std::shared_ptr<T> add = std::make_shared<T>(std::forward<Args>(args)...);
        passes.push_back(add);
        std::sort(passes.begin(), passes.end(), [](const std::shared_ptr<RenderPass>& a, const std::shared_ptr<RenderPass>& b) {
            return a->priority < b->priority;
        });
        return add;
    }
    template <typename T>
    std::shared_ptr<T> get_pass()
    {
        for (int i = 0; i < passes.size(); i++)
        {
            auto &r = *passes[i].get();
            if (typeid(T) == typeid(r))
            {
                return std::dynamic_pointer_cast<T>(passes[i]);
            }
        }
        return std::shared_ptr<T>();
    }
    template <typename T>
    bool remove_pass()
    {
        for (int i = 0; i < passes.size(); i++)
        {
            auto &r = *passes[i].get();
            if (typeid(T) == typeid(r))
            {
                passes.erase(passes.begin() + i);
                return true;
            }
        }
        return false;
    }
};

#endif