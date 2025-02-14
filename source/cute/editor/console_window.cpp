#include "console_window.h"
#include "editor.h"
#include "stat_window.h"
void ConsoleWindow::draw()
{
    bool reclaim_focus = false;
    if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent))
    {
        open = !open;
        reclaim_focus = true;
    }
    if (!open)
    {
        return;
    }
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 window_pos(10.f, viewport->WorkSize.y - 10.f);
    ImVec2 window_pos_pivot(0.f, 1.f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.75f);
    ImGui::Begin("ConsoleWindow", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove);
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ConsoleScroll", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
    {
        for (const auto line : lines)
        {
            ImGui::TextUnformatted(line.c_str());
        }
    }
    ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    ImGui::Separator();
    ImGui::PushItemWidth(-1);
    if (ImGui::InputText("##ConsoleInput", input_buffer, IM_ARRAYSIZE(input_buffer), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        execute(std::string(input_buffer));
        input_buffer[0] = '\0';
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
    {
        ImGui::SetKeyboardFocusHere(-1);
    }
    ImGui::End();
}
void ConsoleWindow::execute(const std::string cmd)
{
    lines.push_back(cmd);
    if (cmd == "cls")
    {
        lines.clear();
    }
    else if (cmd == "stat")
    {
        std::shared_ptr<StatWindow> window = Editor::instance->get_window<StatWindow>();
        window->open = !window->open;
    }
    else if (cmd == "exit")
    {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), 1);
    }
}