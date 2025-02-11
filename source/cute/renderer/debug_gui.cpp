#include "debug_gui.h"
void debug_gui_init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameBorderSize = 1.f;
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        float luminance = style.Colors[i].x * 0.2125f + style.Colors[i].y * 0.7154f + style.Colors[i].z * 0.0721f;
        luminance = luminance * luminance * (3.f - 2.f * luminance);
        style.Colors[i] = ImVec4(luminance, luminance, luminance, style.Colors[i].w);
    }
    
}
void debug_gui_render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void debug_gui_update()
{
    if (glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
    }
    else
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
}
void shutdown_debug_gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}