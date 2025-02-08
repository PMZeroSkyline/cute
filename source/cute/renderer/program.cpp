#include "program.h"
#include "platform/graphics_wrapper/buffer.h"
#include "core/object_handle/get_or_make.h"

Program::Program(std::shared_ptr<VertexShader> _vertex, std::shared_ptr<FragmentShader> _fragment) : vertex(_vertex), fragment(_fragment)
{
    id = glCreateProgram();
    link();
    // bind_active_uniform_blocks();
}
Program::~Program()
{
    if (id != -1)
    {
        glDeleteProgram(id);
    }
}
void Program::link()
{
    std::vector<std::shared_ptr<Shader>> stages = {vertex, fragment};
    for (int i = 0; i < stages.size(); i++)
    {
        glAttachShader(id, stages[i]->id);
    }
    glLinkProgram(id);
    int succ;
    char info[1024];
    glGetProgramiv(id, GL_LINK_STATUS, &succ);
    if (!succ)
    {
        glGetProgramInfoLog(id, 1024, NULL, info);
        std::cout << "failed to link ";
        for (int i = 0; i < stages.size(); i++)
        {
            std::cout << stages[i]->path << " ";
        }
        std::cout << info << std::endl;
        glDeleteProgram(id);
        id = -1;
    }
}
void Program::use() const
{
    glUseProgram(id);
}
void Program::uniform1i(const HashedString &name, bool value)
{
    glUniform1i(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), (int)value);
}
void Program::uniform1i(const HashedString &name, int value)
{
    glUniform1i(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), value);
}
void Program::uniform1f(const HashedString &name, float value)
{
    glUniform1f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), value);
}
void Program::uniform2f(const HashedString &name, const vec2 &v)
{
    glUniform2f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), v.x, v.y);
}
void Program::uniform2f(const HashedString &name, float x, float y)
{
    glUniform2f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), x, y);
}
void Program::uniform3f(const HashedString &name, const vec3 &v)
{
    glUniform3f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), v.x, v.y, v.z);
}
void Program::uniform3f(const HashedString &name, float x, float y, float z)
{
    glUniform3f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), x, y, z);
}
void Program::uniform4f(const HashedString &name, const vec4 &v)
{
    glUniform4f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), v.x, v.y, v.z, v.w);
}
void Program::uniform4fv(const HashedString &name, const std::vector<vec4> &vecs)
{
    glUniform4fv(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), vecs.size(), &vecs.data()->x);
}
void Program::uniform4f(const HashedString &name, float x, float y, float z, float w)
{
    glUniform4f(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), x, y, z, w);
}
void Program::uniform_matrix3f(const HashedString &name, const mat3 &mat)
{
    glUniformMatrix3fv(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), 1, GL_FALSE, mat.data());
}
void Program::uniform_matrix4fv(const HashedString &name, GLsizei count, const mat4* value)
{
    glUniformMatrix4fv(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), count, GL_FALSE, (GLfloat*)value);
}
void Program::uniform_matrix4f(const HashedString &name, const mat4 &mat)
{
    uniform_matrix4fv(name, 1, &mat);
}
void Program::uniform_matrix3s(const HashedString &name, const std::vector<mat3> &mats)
{
    glUniformMatrix3fv(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), mats.size(), GL_FALSE, mats.data()->data());
}
void Program::uniform_matrix4s(const HashedString &name, const std::vector<mat4> &mats)
{
    glUniformMatrix4fv(get_or_make(locations, name, [this, &name](){return glGetUniformLocation(id, name.str->c_str());}), mats.size(), GL_FALSE, mats.data()->data());
}
void Program::uniform_block_binding(const std::string &name, GLuint uniform_block_binding)
{
    glUniformBlockBinding(id, glGetUniformLocation(id, name.c_str()), uniform_block_binding);
}
void Program::bind_active_uniform_blocks()
{
    GLint blocks;
    glGetProgramiv(id, GL_ACTIVE_UNIFORM_BLOCKS, &blocks);
    for (GLint i = 0; i < blocks; ++i) {
        GLint len;
        glGetActiveUniformBlockiv(id, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &len);
        std::vector<GLchar> vec(len);
        glGetActiveUniformBlockName(id, i, len, nullptr, vec.data());
        std::string block_name(vec.data());
        std::unordered_map<std::string, GLuint>::iterator it = Buffer::binding.find(block_name);
        if (it != Buffer::binding.end()) 
        {
            uniform_block_binding(block_name, it->second);
        }
        else {
            std::cout << "bind uniform buffer failed " << block_name << std::endl;
        }
    }
}
std::shared_ptr<Program> Program::get(const std::string& vert_uri, const std::string& frag_uri)
{
    return get_or_make(weak, vert_uri+","+frag_uri, [&vert_uri,&frag_uri](){
        return std::make_shared<Program>(VertexShader::get(vert_uri), FragmentShader::get(frag_uri));
    });
}
