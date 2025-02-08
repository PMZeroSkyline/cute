#ifndef OPENGL_API_H
#define OPENGL_API_H

#include "../graphics_api.h"
#include <set>
#include <string>

struct OpenglAPI : GraphicsAPI
{
    int version = 0;
    int language_version = 0;
    std::string version_profile = "core";
    std::set<std::string> extensions;
    OpenglAPI();
    void swap_buffers() override;
};

#endif