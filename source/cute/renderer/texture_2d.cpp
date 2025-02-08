#include "texture_2d.h"
#include "core/object_handle/get_or_make.h"

Texture2D::Texture2D(const std::vector<std::shared_ptr<Image>>& _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : mipmaps(_mipmaps), border(_border), Texture(_name, _sampler, _internalformat, _format) 
{
    bind();
    parse_internalformat(mipmaps[0]->component, mipmaps[0]->type);
    parse_format(mipmaps[0]->component);
    sampler->tex_parameter(get_target());
    if (mipmap && mipmaps.size() > 1)
    {
        tex_image(false);
        glGenerateMipmap(get_target());
        tex_image(true);
    }
    else if (mipmap)
    {
        tex_image(true);
        glGenerateMipmap(get_target());
    }
    else
    {
        tex_image(true);
    }
}
Texture2D::Texture2D(const std::shared_ptr<Image>& image, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : Texture2D(std::vector<std::shared_ptr<Image>>(1, image), _name, _sampler, mipmap, _internalformat, _format, _border) {}
Texture2D::Texture2D(unsigned int type, int x, int y, int component, int levels, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : border(_border), Texture(_name, _sampler, _internalformat, _format)
{
    for (int mip = 0; mip < levels; mip++) 
    {
        mipmaps.push_back(std::make_shared<Image>(type, x*std::pow(0.5, mip), y*std::pow(0.5, mip), component, nullptr));
    }
    bind();
    sampler->tex_parameter(get_target());
    parse_internalformat(component, type);
    parse_format(component);
    tex_image(false);
    if (mipmap)
    {
        glGenerateMipmap(get_target());
    }
}
void Texture2D::tex_image(bool wirte_pixels, GLint level)
{
    glTexImage2D(GL_TEXTURE_2D, level, internalformat, mipmaps[level]->x, mipmaps[level]->y, border, format, mipmaps[level]->type, wirte_pixels ? mipmaps[level]->data : nullptr);
}
void Texture2D::tex_image(bool wirte_pixels)
{
    for (int i = 0; i < mipmaps.size(); i++)
    {
        tex_image(wirte_pixels, i);
    }
}
GLenum Texture2D::get_target()
{
    return GL_TEXTURE_2D;
}
std::shared_ptr<Texture2D> Texture2D::get(const std::string& path, bool flip_v, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border, bool resize_power_of_two)
{
    return get_or_make(weak, path, [&path, &flip_v, &resize_power_of_two,&_sampler,&mipmap,&_internalformat,&_format,&_border](){
        std::vector<std::shared_ptr<Image>> _mipmaps;
        _mipmaps.push_back(Image::get(path, flip_v, resize_power_of_two));
        return std::make_shared<Texture2D>(_mipmaps, path, _sampler, mipmap, _internalformat, _format, _border);
    });
}