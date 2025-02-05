#include <iostream>
#include "platform/graphics_wrapper/opengl/opengl_api.h"
#include "interface_devices/desktop/desktop_app.h"
int main()
{
    App::instance = std::make_shared<DesktopApp>();
    App::instance->window = std::make_shared<DesktopWindow>(ivec2(800, 600), "none");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    
    while(App::instance->is_running())
    {
        App::instance->update();
    }
    return 0;
}