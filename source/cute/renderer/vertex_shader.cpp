#include "vertex_shader.h"
#include "core/object_handle/get_or_make.h"

VertexShader::VertexShader(std::string uri) : Shader(uri) 
{
    id = glCreateShader(GL_VERTEX_SHADER);
    compile();
}
std::shared_ptr<VertexShader> VertexShader::get(const std::string& uri)
{
    return get_or_make(weak, uri, [&uri](){
        return std::make_shared<VertexShader>(uri);
    });
}