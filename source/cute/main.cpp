#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include "platform/graphics_wrapper/gl_api.h"
#include "device/app.h"
#include "device/window.h"
#include "resource/world.h"
#include "visual_effect/precompute_lighting.h"
#include "renderer/texture_2d.h"
#include "editor/editor_gui.h"
#include "editor/console_window.h"
#include "editor/status_window.h"


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
    EditorGUI::instance = std::make_shared<EditorGUI>();
    EditorGUI::instance->add_window<ConsoleWindow>();
    EditorGUI::instance->add_window<StatusWindow>();
    while(App::instance->is_running())
    {
        App::instance->update();
        World::instance->scene->update();
        EditorGUI::instance->update();
        glClearColor(0.85f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        EditorGUI::instance->render();
        GraphicsAPI::instance->swap_buffers();
    }
    
    return 0;
}