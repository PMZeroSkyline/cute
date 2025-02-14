#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <unordered_map>
#include "platform/graphics_wrapper/gl_validation.h"
#include "core/parser/json.h"
#include "core/math/vec2.h"
#include "core/math/vec4.h"
#include "core/string/hashed_string.h"
#include "renderer/texture.h"
#include "renderer/program.h"
#define OPAQUE_ALPHA_BIT   0b00000000000000000000000000000001
#define MASK_ALPHA_BIT     0b00000000000000000000000000000010
#define BLEND_ALPHA_BIT    0b00000000000000000000000000000100
struct Material
{
    std::string name;
    unsigned int alpha_mode = OPAQUE_ALPHA_BIT; // OPAQUE:1, MASK:2, BLEND:4
    GLboolean depth_test = GL_FALSE;
    GLboolean depth_mask = GL_TRUE;
    GLenum depth_func = GL_LESS;
    GLboolean blend = GL_FALSE;
    GLenum blend_func_sfactor = GL_ONE;
    GLenum blend_func_dfactor = GL_ZERO;
    GLboolean cull_face = GL_FALSE;
    GLenum cull_face_mode = GL_BACK;
    GLenum polygon_mode_face = GL_FRONT_AND_BACK;
    GLenum polygon_mode_mode = GL_FILL;
    std::unordered_map<HashedString, float> floats;
    std::unordered_map<HashedString, vec2> vec2s;
    std::unordered_map<HashedString, vec3> vec3s;
    std::unordered_map<HashedString, vec4> vec4s;
    std::unordered_map<HashedString, std::shared_ptr<Texture>> textures;
    static inline std::unordered_map<HashedString, std::shared_ptr<Texture>> g_textures;
    std::unordered_map<HashedString, std::shared_ptr<Program>> programs;
    Material() = default;
    Material(const std::shared_ptr<Program>& _program);
    Material(const json& j, const std::vector<std::shared_ptr<Texture>>& _textures);
    void submit_state();
    void submit_uniform(Program* program);
    void submit(Program* program);
    Program* require(const HashedString& defines);
    static std::shared_ptr<Material> make_default();
};

#endif