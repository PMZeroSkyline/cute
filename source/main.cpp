#include <iostream>
#include "platform/graphics_wrapper/opengl/opengl_api.h"
#include "device/desktop/desktop_app.h"
int main()
{
    App::instance = std::make_shared<DesktopApp>();
    App::instance->window = std::make_shared<DesktopWindow>(ivec2(800, 600), "none");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    
    while(App::instance->is_running())
    {
        App::instance->update();
        glClearColor(0.85f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        GraphicsAPI::instance->swap_buffers();
    }
    return 0;
}