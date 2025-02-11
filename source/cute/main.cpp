#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include "platform/graphics_wrapper/gl_api.h"
#include "device/desktop_app.h"
#include "device/desktop_window.h"
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

    App::instance = std::make_shared<DesktopApp>();
    App::instance->window = std::make_shared<DesktopWindow>(ivec2(800, 600), "none");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    debug_gui_init();

    auto lut = render_brdf_lut();
    
    while(App::instance->is_running())
    {
        App::instance->update();
        World::instance->scene->update();
        debug_gui_update();
        glClearColor(0.85f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        // render_ibl_specular(render_texture_cube("assets/texture/cobblestone_street_night_2k.hdr", 512), 128);
        ImGui::Begin("test");
        ImGui::Image(lut->id, ImVec2(128, 128));
        ImGui::End();
        
        debug_gui_render();
        GraphicsAPI::instance->swap_buffers();
    }
    debug_gui_shutdown();

    
    return 0;
}