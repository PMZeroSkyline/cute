#include "editor.h"
#include "renderer/debug_gui.h"
#include "device/app.h"
static void draw_debug_fps()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 window_pos(viewport->WorkSize.x - 10.f, 10.f);
    ImVec2 window_pos_pivot(1.f, 0.f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("overlay_debug", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove);
    ImGui::Text("       debug       ");
    ImGui::Separator();
    ImGui::Text("fps    : %.1f", 1.f / App::instance->delta_time);
    ImGui::Text("ms     : %.1f", App::instance->delta_time * 1000.f);
    ImGui::End();
}
void draw_editor()
{
    draw_debug_fps();
}