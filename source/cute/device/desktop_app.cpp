#include "desktop_app.h"
#include "platform/graphics_wrapper/gl_validation.h"
#include <GLFW/glfw3.h>
#include "platform/platform_detection.h"

DesktopApp::DesktopApp()
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
DesktopApp::~DesktopApp()
{
    glfwTerminate();
}
bool DesktopApp::is_running()
{
    return window->is_open();
}
void DesktopApp::poll_events()
{
    glfwPollEvents();
}
