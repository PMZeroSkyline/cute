#ifndef OPENGL_API_H
#define OPENGL_API_H

#include "../graphics_api.h"
#include "opengl_defines.h"
#include "opengl_validation.h"
#include <glfw/glfw3.h>
#include "core/debug/log.h"

#include <sstream>
#include <set>
#include <map>
#include "interface_devices/desktop/desktop_app.h"

struct OpenglAPI : GraphicsAPI
{
    int ver = 0;
    int lang_ver = 0;
    std::set<std::string> extensions;
    OpenglAPI();
    void swap_buffers() override;
};

#endif