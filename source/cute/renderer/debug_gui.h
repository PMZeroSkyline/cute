#ifndef DEBUG_GUI_H
#define DEBUG_GUI_H

#include "platform/graphics_wrapper/gl/gl_validation.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void debug_gui_init();
void debug_gui_render();
void debug_gui_update();
void debug_gui_shutdown();

#endif