#include "texture_cube.h"
#include "core/string/string.h"
#include "core/object_handle/get_or_make.h"

TextureCube::TextureCube(std::vector<std::array<std::shared_ptr<Image>, 6>> _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : mipmaps(_mipmaps), border(_border), Texture(_name, _sampler, _internalformat, _format)
{
    bind();
    parse_internalformat(mipmaps[0][0]->component, mipmaps[0][0]->type);
    parse_format(mipmaps[0][0]->component);
    sampler->submit_parameter(get_target());
    if (mipmap && mipmaps.size() > 1)
    {
        submit(false);
        glGenerateMipmap(get_target());
        submit(true);
    }
    else if (mipmap)
    {
        submit(true);
        glGenerateMipmap(get_target());
    }
    else
    {
        submit(true);
    }
}
TextureCube::TextureCube(std::array<std::shared_ptr<Image>, 6> faces, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : TextureCube(std::vector<std::array<std::shared_ptr<Image>, 6>>(1, faces), _name, _sampler, mipmap, _internalformat, _format, _border) {}
TextureCube::TextureCube(unsigned int type, int size, int component, int levels, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : border(_border), Texture(_name, _sampler, _internalformat, _format)
{
    for (int mip = 0; mip < levels; mip++)
    {
        unsigned int mipSize  = size * std::pow(0.5, mip);
        std::shared_ptr<Image> right = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::shared_ptr<Image> left = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::shared_ptr<Image> top = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::shared_ptr<Image> bottom = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::shared_ptr<Image> front = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::shared_ptr<Image> back = std::make_shared<Image>(type, mipSize, mipSize, component, nullptr);
        std::array<std::shared_ptr<Image>, 6> faces = {right, left, top, bottom, front, back};
        mipmaps.push_back(faces);
    }
    bind();
    sampler->submit_parameter(get_target());
    parse_internalformat(component, type);
    parse_format(component);
    submit(false);
    #if !defined(PLATFORM_ANDROID) && !defined(PLATFORM_IOS)
    if (mipmap)
    {
        glGenerateMipmap(get_target());
    }
    #endif
}
void TextureCube::submit(bool wirtePixels, GLint level)
{
    for (int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, internalformat, mipmaps[level][i]->x, mipmaps[level][i]->y, border, format, mipmaps[level][i]->type, wirtePixels ? mipmaps[level][i]->data : nullptr);
    }
}
void TextureCube::submit(bool wirtePixels)
{
    for (int i = 0; i < mipmaps.size(); i++)
    {
        submit(wirtePixels, i);
    }
}
GLenum TextureCube::get_target()
{
    return GL_TEXTURE_CUBE_MAP;
}
static std::array<quat, 6> orientations()
{   
    float x = .5f;
    float y = .707107f;
    return {quat(-x,x,x,-x),quat(x,x,x,x),quat(1.f,0.f,0.f,0.f),quat(0.f,0.f,0.f,1.f),quat(y,0.f,0.f,y),quat(0.f,y,y,0.f)};
}
std::shared_ptr<TextureCube> TextureCube::get(const std::string& uris, bool flip_v, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border)
{
    return get_or_make(weak, uris, [&uris, &flip_v,&_sampler,&mipmap,&_internalformat,&_format,&_border](){
        std::vector<std::array<std::shared_ptr<Image>, 6>> _mipmaps;
        std::vector<std::string> tokens = split(uris, ',') ;
        std::array<std::shared_ptr<Image>, 6> faces;
        for (int i = 0; i < tokens.size(); i++)
        {
            faces[i % 6] = Image::get(tokens[i], flip_v, true);
            if ((i+1) % 6 == 0)
            {
                _mipmaps.push_back(faces);
            }
        }
        return std::make_shared<TextureCube>(_mipmaps, uris, _sampler, mipmap, _internalformat, _format, _border);
    });
}
std::shared_ptr<TextureCube> TextureCube::make_test(int size, bool mipmap)
{
    std::shared_ptr<Image> i0 = std::make_shared<Image>(size, size, vec4(1.f, 0.f, 0.f, 1.f));
    std::shared_ptr<Image> i1 = std::make_shared<Image>(size, size, vec4(0.f, 1.f, 1.f, 1.f));
    std::shared_ptr<Image> i2 = std::make_shared<Image>(size, size, vec4(0.f, 1.f, 0.f, 1.f));
    std::shared_ptr<Image> i3 = std::make_shared<Image>(size, size, vec4(1.f, 0.f, 1.f, 1.f));
    std::shared_ptr<Image> i4 = std::make_shared<Image>(size, size, vec4(0.f, 0.f, 1.f, 1.f));
    std::shared_ptr<Image> i5 = std::make_shared<Image>(size, size, vec4(1.f, 1.f, 0.f, 1.f));
    std::array<std::shared_ptr<Image>, 6> faces = {i0, i1, i2, i3, i4, i5};
    return std::make_shared<TextureCube>(faces, "", mipmap ? TextureSampler::make_linear_mipmap_clamp_to_edge() : TextureSampler::make_linear_clamp_to_edge(), mipmap);
}
std::shared_ptr<TextureCube> TextureCube::make_color(int size, u8vec4 color, bool mipmap)
{
    std::shared_ptr<Image> i = std::make_shared<Image>(size, size, color);
    std::array<std::shared_ptr<Image>, 6> faces = {i, i, i, i, i, i};
    return std::make_shared<TextureCube>(faces, "", mipmap ? TextureSampler::make_linear_mipmap_clamp_to_edge() : TextureSampler::make_linear_clamp_to_edge(), mipmap);
}