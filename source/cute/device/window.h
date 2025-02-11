#ifndef DESKTOP_WINDOW_H
#define DESKTOP_WINDOW_H

#include "cursor.h"
#include "key.h"
#include "platform/graphics_wrapper/gl_validation.h"
#include <GLFW/glfw3.h>
#include <array>

struct Window
{
    std::array<Key, GLFW_KEY_LAST> keys;
    Cursor cursor;
    std::string name;
    ivec2 window_size;
    ivec2 render_size;
    GLFWwindow* glfw_window;
    static inline std::vector<Window*> windows;
    Window(ivec2 size, const std::string& _name);
    ~Window();
    void on_set_key(int key, int scancode, int action, int mods);
    void on_set_cursor_pos(double xpos, double ypos);
    void on_set_framebuffer_size(int width, int height);
    void on_set_mouse_button(int button, int action, int mods);
    bool is_open() const;
    void reset_input();

};



#endif

