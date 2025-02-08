#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include "platform/graphics_wrapper/gl/gl_api.h"
#include "device/desktop/desktop_app.h"
#include "device/desktop/desktop_window.h"
#include "scene_graph/world.h"
#include "renderer/debug_gui.h"
int main(int argc, char** argv)
{
    #ifdef WIN_OS
    fs::current_path(fs::current_path().parent_path().parent_path());
    #endif
    #ifdef MAC_OS
    fs::current_path(fs::current_path().parent_path());
    #endif

    App::instance = std::make_shared<DesktopApp>();
    App::instance->window = std::make_shared<DesktopWindow>(ivec2(800, 600), "none");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    debug_gui_init();

    float test;

    while(App::instance->is_running())
    {
        App::instance->update();
        debug_gui_update();
        glClearColor(0.85f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Test");
        ImGui::SliderFloat("test", &test, 0.f, 1.f);
        ImGui::End();

        debug_gui_render();
        GraphicsAPI::instance->swap_buffers();
    }
    debug_gui_shutdown();

    
    return 0;
}