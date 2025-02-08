#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include "shader.h"
#include <unordered_map>
struct FragmentShader : Shader
{
    FragmentShader(std::string uri);
    static inline std::unordered_map<std::string, std::weak_ptr<FragmentShader>> weak;
    static std::shared_ptr<FragmentShader> get(const std::string& uri);
};

#endif