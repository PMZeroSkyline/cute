#include "texture_sampler.h"
#include "platform/graphics_wrapper/gl/gl_extension_defines.h"
#include "platform/graphics_wrapper/gl/gl_api.h"

TextureSampler::TextureSampler(GLint _magFilter,GLint _minFilter,GLint _wrapS,GLint _wrapT,GLint _wrapR,GLfloat _max_anisotropy,vec4 _border_color,const std::string& _name) : mag_filter(_magFilter),min_filter(_minFilter),wrap_s(_wrapS),wrap_t(_wrapT),wrap_r(_wrapR),max_anisotropy(_max_anisotropy),border_color(_border_color),name(_name) {}
TextureSampler::~TextureSampler() {}
void TextureSampler::tex_parameter(GLenum target)
{
    if (mag_filter)
    {
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
    }
    if (min_filter)
    {
        #if defined(PLATFORM_ANDROID) || defined(PLATFORM_IOS)
        if (target == GL_TEXTURE_CUBE_MAP && minFilter == GL_LINEAR_MIPMAP_LINEAR)
        {
            minFilter = GL_LINEAR;
        }
        #endif
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
    }
    if (wrap_s)
    {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
    }
    if (wrap_t)
    {
        glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);
    }
    if (target == GL_TEXTURE_CUBE_MAP && wrap_r)
    {
        glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap_r);
    }
    if (max_anisotropy && ((OpenglAPI*)GraphicsAPI::instance.get())->extensions.count(GL_ARB_TEXTURE_FILTER_ANISOTROPIC_EXTENSION_NAME))
    {
        GLfloat supported_max;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &supported_max);
        GLfloat anisotropy = std::min(max_anisotropy, supported_max);
        glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
    }
    if (border_color != vec4(-1.f))
    {
        glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, &border_color[0]);
    }
}
std::shared_ptr<TextureSampler> TextureSampler::make_nearest_clamp(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_NEAREST, GL_NEAREST, GL_CLAMP, GL_CLAMP, GL_CLAMP, _max_anisotropy, _border_color, "NearestClamp");
}
std::shared_ptr<TextureSampler> TextureSampler::make_nearest_clamp_to_border(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, _max_anisotropy, _border_color, "NearestClampToBorder");
}
std::shared_ptr<TextureSampler> TextureSampler::make_linear_repeat(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_REPEAT, _max_anisotropy, _border_color, "LinearRepeat");
}
std::shared_ptr<TextureSampler> TextureSampler::make_linear_clamp_to_edge(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, _max_anisotropy, _border_color, "LinearClampToEdge");
}
std::shared_ptr<TextureSampler> TextureSampler::make_linear_mipmap_clamp_to_edge(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, _max_anisotropy, _border_color, "LinearMipmapClampToEdge");
}
std::shared_ptr<TextureSampler> TextureSampler::make_linear_mipmap_repeat(GLfloat _max_anisotropy, const vec4& _border_color)
{
    return std::make_shared<TextureSampler>(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_REPEAT, _max_anisotropy, _border_color, "LinearMipmapRepeat");
}
void from_json(const json& j, TextureSampler& s) 
{
	if (j.contains("magFilter"))
    {
        s.mag_filter = j["magFilter"];
    }
    if (j.contains("minFilter"))
    {
        s.min_filter = j["minFilter"];
    }
    if (j.contains("wrapS"))
    {
        s.wrap_s = j["wrapS"];
    }
    if (j.contains("wrapT"))
    {
        s.wrap_t = j["wrapT"];
    }
    if (j.contains("name"))
    {
        s.name = j["name"];
    }
    if (j.contains("maxAnisotropy"))
    {
        s.max_anisotropy = j["maxAnisotropy"];
    }
    else
    {
        s.max_anisotropy = 4;
    }
}