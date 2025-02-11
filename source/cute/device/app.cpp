#include "app.h"
#include "platform/graphics_wrapper/gl_validation.h"
#include <GLFW/glfw3.h>
#include "platform/platform_detection.h"
App::App()
{
    glfwInit();
    #ifdef WIN_OS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    #endif
    #ifdef MAC_OS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}
App::~App()
{
    glfwTerminate();
}
bool App::is_running()
{
    return window->is_open();
}
void App::poll_events()
{
    glfwPollEvents();
}
void App::update_timer()
{
    if (!timer)
    {
        timer = std::make_shared<HiResTimer>();
    }
    float elapsed = timer->elapsed();
    delta_time = elapsed - time;
    time = elapsed;
}
void App::update() 
{
    update_timer();
    window->reset_input();
    poll_events();
};