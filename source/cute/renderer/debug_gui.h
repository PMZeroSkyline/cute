#ifndef DEBUG_GUI_H
#define DEBUG_GUI_H

#include "platform/graphics_wrapper/gl_validation.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void init_debug_gui();
void draw_debug_gui();
void update_debug_gui();
void shutdown_debug_gui();

#endif