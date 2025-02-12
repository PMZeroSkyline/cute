#include "console_window.h"
#include "editor_gui.h"
#include "status_window.h"
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
    ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.75f);
    ImGui::Begin("Console", &open, ImGuiWindowFlags_NoTitleBar);
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
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
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
        lines.clear();
    if (cmd == "status")
    {
        std::shared_ptr<StatusWindow> window = EditorGUI::instance->get_window<StatusWindow>();
        window->open = !window->open;
    }
}