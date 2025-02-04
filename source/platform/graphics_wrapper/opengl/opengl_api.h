#ifndef OPENGL_API_H
#define OPENGL_API_H

#include "../graphics_api.h"
#include "opengl_defines.h"
#include "opengl_validation.h"
#include "core/debug/log.h"
#include <sstream>
#include <set>
#include <map>
#include <glad/glad.h>
#include <glfw/glfw3.h>

struct OpenglAPI : GraphicsAPI
{
    int ver = 0;
    int lang_ver = 0;
    std::set<std::string> extensions;
    OpenglAPI();
};

#endif