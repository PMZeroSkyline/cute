#ifndef DEBUG_GUI_H
#define DEBUG_GUI_H

#include "platform/graphics_wrapper/gl_validation.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "editor_window.h"
#include <vector>

struct Editor
{
    std::vector<std::shared_ptr<EditorWindow>> windows;
    static inline std::shared_ptr<Editor> instance = nullptr;
    Editor();
    virtual ~Editor();
    void update();
    void render();
    template <typename T, typename... Args>
    std::shared_ptr<T> add_window(Args &&...args)
    {
        std::shared_ptr<T> add = std::make_shared<T>(std::forward<Args>(args)...);
        windows.push_back(add);
        return add;
    }
    template <typename T>
    std::shared_ptr<T> get_window()
    {
        for (int i = 0; i < windows.size(); i++)
        {
            auto &r = *windows[i].get();
            if (typeid(T) == typeid(r))
            {
                return std::dynamic_pointer_cast<T>(windows[i]);
            }
        }
        return std::shared_ptr<T>();
    }
    template <typename T>
    bool remove_window()
    {
        for (int i = 0; i < windows.size(); i++)
        {
            auto &r = *windows[i].get();
            if (typeid(T) == typeid(r))
            {
                windows.erase(windows.begin() + i);
                return true;
            }
        }
        return false;
    }
};
#endif