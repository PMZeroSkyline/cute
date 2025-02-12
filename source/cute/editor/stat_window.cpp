#include "stat_window.h"
#include "editor.h"
#include "device/app.h"

void StatWindow::draw()
{
    if (!open)
    {
        return;
    }
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 window_pos(viewport->WorkSize.x - 10.f, 10.f);
    ImVec2 window_pos_pivot(1.f, 0.f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("StatWindow", &open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::Text("fps %.1f", 1.f / App::instance->delta_time);
    ImGui::Text("ms  %.1f", App::instance->delta_time * 1000.f);
    ImGui::End();
}