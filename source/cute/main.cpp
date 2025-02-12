#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include "platform/graphics_wrapper/gl_api.h"
#include "device/app.h"
#include "device/window.h"
#include "resource/world.h"
#include "renderer/texture_2d.h"
#include "renderer/engine/render_engine.h"
#include "renderer/engine/render_world.h"
#include "editor/editor.h"
#include "editor/console_window.h"
#include "editor/stat_window.h"


int main(int argc, char** argv)
{
    #ifdef WIN_OS
    fs::current_path(fs::current_path().parent_path().parent_path());
    #endif
    #ifdef MAC_OS
    fs::current_path(fs::current_path().parent_path());
    #endif
    App::instance = std::make_shared<App>();
    App::instance->window = std::make_shared<Window>(ivec2(800, 600), "cute");
    GraphicsAPI::instance = std::make_shared<OpenglAPI>();
    RenderEngine::instance = std::make_shared<RenderEngine>();
    RenderWorld::instance = std::make_shared<RenderWorld>();
    Editor::instance = std::make_shared<Editor>();
    Editor::instance->add_window<ConsoleWindow>();
    Editor::instance->add_window<StatWindow>();
    while(App::instance->is_running())
    {
        App::instance->update();
        World::instance->scene->update();
        Editor::instance->update();
        RenderWorld::instance->update();
        glClearColor(.5f, .5f, .5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        RenderEngine::instance->render();
        Editor::instance->render();
        GraphicsAPI::instance->swap_buffers();
    }
    return 0;
}