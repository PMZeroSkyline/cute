#ifndef PROGRAM_H
#define PROGRAM_H

#include "vertex_shader.h"
#include "fragment_shader.h"
#include "core/math/mat4.h"
#include "core/string/hashed_string.h"

struct Program
{
public:
    GLuint id = -1;
    std::shared_ptr<VertexShader> vertex;
    std::shared_ptr<FragmentShader> fragment;
    std::unordered_map<HashedString, GLint> locations;
    static inline std::unordered_map<HashedString, std::shared_ptr<Program>> shared = std::unordered_map<HashedString, std::shared_ptr<Program>>();
    Program() = default;
    Program(std::shared_ptr<VertexShader> _vertex, std::shared_ptr<FragmentShader> _fragment);
    virtual ~Program();
    void link();
    void use() const;
    void uniform1i(const HashedString &name, bool value);
    void uniform1i(const HashedString &name, int value);
    void uniform1f(const HashedString &name, float value);
    void uniform2f(const HashedString &name, const vec2 &v);
    void uniform2f(const HashedString &name, float x, float y);
    void uniform3f(const HashedString &name, const vec3 &v);
    void uniform3f(const HashedString &name, float x, float y, float z);
    void uniform4f(const HashedString &name, const vec4 &v);
    void uniform4fv(const HashedString &name, const std::vector<vec4> &vecs);
    void uniform4f(const HashedString &name, float x, float y, float z, float w);
    void uniform_matrix3f(const HashedString &name, const mat3 &mat);
    void uniform_matrix4fv(const HashedString &name, GLsizei count, const mat4* value);
    void uniform_matrix4f(const HashedString &name, const mat4 &mat);
    void uniform_matrix3s(const HashedString &name, const std::vector<mat3> &mats);
    void uniform_matrix4s(const HashedString &name, const std::vector<mat4> &mats);
    void uniform_block_binding(const std::string &name, GLuint uniform_block_binding);
    void bind_active_uniform_blocks();
    static inline std::unordered_map<std::string, std::weak_ptr<Program>> weak;
    static std::shared_ptr<Program> get(const std::string& vert_uri, const std::string& frag_uri);
};

#endif