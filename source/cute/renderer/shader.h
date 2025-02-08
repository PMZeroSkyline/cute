#ifndef SHADER_H
#define SHADER_H

#include "platform/graphics_wrapper/gl/gl_validation.h"
#include <set>
#include <string>
#include <vector>

struct Shader
{
    std::string path;
    GLuint id = -1;
    std::set<std::string> defines;
    Shader() = default;
    Shader(const std::string& uri);
    virtual ~Shader();
    std::string uri() const;
    void compile();
    void preprocessor(const std::string& path, std::string& code, std::vector<std::string>& file_names);
    void compile(const std::string& code, std::vector<std::string>* file_names = nullptr);
};

#endif