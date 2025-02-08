#ifndef TEXTURE_SAMPLER_H
#define TEXTURE_SAMPLER_H

#include <string>
#include "platform/graphics_wrapper/gl/gl_validation.h"
#include "core/math/vec4.h"
#include "core/parser/json.h"
struct TextureSampler
{
    std::string name;
    GLint mag_filter = 0;
    GLint min_filter = 0;
    GLint wrap_s = 0;
    GLint wrap_t = 0;
    GLint wrap_r = 0;
    GLfloat max_anisotropy = 0;
    vec4 border_color = vec4(-1.f);
    TextureSampler() = default;
    TextureSampler(GLint _mag_filter, GLint _min_filter = 0, GLint _wrap_s = 0, GLint _wrap_t = 0, GLint _wrap_r = 0, GLfloat _max_anisotropy = 0, vec4 _border_color = vec4(-1.f), const std::string& _name = "");
    ~TextureSampler();
    void submit_parameter(GLenum target);
    static std::shared_ptr<TextureSampler> make_nearest_clamp(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
    static std::shared_ptr<TextureSampler> make_nearest_clamp_to_border(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
    static std::shared_ptr<TextureSampler> make_linear_repeat(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
    static std::shared_ptr<TextureSampler> make_linear_clamp_to_edge(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
    static std::shared_ptr<TextureSampler> make_linear_mipmap_clamp_to_edge(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
    static std::shared_ptr<TextureSampler> make_linear_mipmap_repeat(GLfloat _max_anisotropy = 0, const vec4& _border_color = vec4(-1.f));
};
void from_json(const json& j, TextureSampler& s);
#endif