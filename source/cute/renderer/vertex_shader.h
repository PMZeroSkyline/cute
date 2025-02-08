#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "shader.h"
#include <unordered_map>

struct VertexShader : Shader
{
    VertexShader(std::string uri);
    static inline std::unordered_map<std::string, std::weak_ptr<VertexShader>> weak;
    static std::shared_ptr<VertexShader> get(const std::string& uri);
};

#endif