#include "desktop_window.h"

DesktopWindow::DesktopWindow(ivec2 size, const std::string& _name) : name(_name), window_size(size)
{
    windows.push_back(this);

    render_size = window_size;
    #ifdef MAC_OS
    render_size *= 2;
    #endif
    
    glfw_window = glfwCreateWindow(window_size.x, window_size.y, name.c_str(), NULL, NULL);
    if (!glfw_window)
        std::cout << "failed create window" << std::endl;
    
    glfwMakeContextCurrent(glfw_window);
        
    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetKeyCallback(glfw_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        ((DesktopWindow*)glfwGetWindowUserPointer(window))->on_set_key(key, scancode, action, mods);
    });
    glfwSetCursorPosCallback(glfw_window, [](GLFWwindow* window, double xpos, double ypos){
        ((DesktopWindow*)glfwGetWindowUserPointer(window))->on_set_cursor_pos(xpos, ypos);
    });
    glfwSetFramebufferSizeCallback(glfw_window, [](GLFWwindow* window, int width, int height){
        ((DesktopWindow*)glfwGetWindowUserPointer(window))->on_set_framebuffer_size(width, height);
    });
    glfwSetMouseButtonCallback(glfw_window, [](GLFWwindow* window, int button, int action, int mods){
        ((DesktopWindow*)glfwGetWindowUserPointer(window))->on_set_mouse_button(button, action, mods);
    });
}
DesktopWindow::~DesktopWindow()
{
    auto it = std::find(windows.begin(), windows.end(), this);
    if (it != windows.end())
    {
        windows.erase(it);
    }
    glfwDestroyWindow(glfw_window);
}
void DesktopWindow::on_set_key(int key, int scancode, int action, int mods)
{
    if (action == 0)
        keys[key].set(false);
    else if (action == 1)
        keys[key].set(true);
}
void DesktopWindow::on_set_cursor_pos(double xpos, double ypos)
{
    const vec2 p = vec2(xpos, ypos);

    if (cursor.pos != vec2(FLT_MAX))
        cursor.dt_pos += cursor.pos - p; // here MUST use add, has multiple event in one frame

    cursor.pos = p;
}
void DesktopWindow::on_set_framebuffer_size(int width, int height)
{
    window_size = vec2(width, height);
    render_size = window_size;
    
    #ifdef MAC_OS
    render_size *= 2;
    #endif
}
void DesktopWindow::on_set_mouse_button(int button, int action, int mods)
{
    if (action == 0)
        keys[button].set(false);
    else if (action == 1)
        keys[button].set(true);
}
bool DesktopWindow::is_open() const
{
    return !glfwWindowShouldClose(glfw_window);
}
void DesktopWindow::reset_input()
{
    for (auto& k : keys)
    {
        k.reset();
    }
    cursor.dt_pos = vec2();
}