#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include "platform/graphics_wrapper/gl_api.h"
#include "device/app.h"
#include "device/window.h"
#include "resource/world.h"
#include "renderer/debug_gui.h"
#include "visual_effect/precompute_lighting.h"
#include "renderer/texture_2d.h"


int main(int argc, char** argv)
{
    #ifdef WIN_OS
    fs::current_path(fs::current_path().parent_path().parent_path());
    #endif
    #ifdef MAC_OS
    fs::current_path(fs::current_path().parent_path());
    #endif

    App::instance = std::make_shared<App>();
    App::instance->window = std::make_shared<Window>(ivec2(800, 600), "none");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    debug_gui_init();

    bool open = true;
    while(App::instance->is_running())
    {
        App::instance->update();
        World::instance->scene->update();
        debug_gui_update();
        glClearColor(0.85f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (App::instance->window->keys[GLFW_KEY_W].down)
        {
            open = !open;
            std::cout << open << std::endl;
        }

        ImGui::ShowDemoWindow(nullptr);
        debug_gui_render();
        GraphicsAPI::instance->swap_buffers();
    }
    shutdown_debug_gui();

    
    return 0;
}