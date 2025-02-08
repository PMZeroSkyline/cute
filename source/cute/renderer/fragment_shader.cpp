#include "fragment_shader.h"
#include "core/object_handle/get_or_make.h"

FragmentShader::FragmentShader(std::string uri) : Shader(uri) 
{
    id = glCreateShader(GL_FRAGMENT_SHADER);
    compile();
}
std::shared_ptr<FragmentShader> FragmentShader::get(const std::string& uri)
{
    return get_or_make(weak, uri, [&](){
        return std::make_shared<FragmentShader>(uri);
    });
}