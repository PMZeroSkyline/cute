#ifndef GUI_H
#define GUI_H

#include "platform/graphics_wrapper/gl/gl_validation.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void gui_init();
void gui_render();
void gui_update();
void shutdown_gui();

#endif