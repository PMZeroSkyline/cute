#include "texture_2d_array.h"

Texture2DArray::Texture2DArray(std::vector<std::vector<std::shared_ptr<Image>>> _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : mipmaps(_mipmaps), border(_border), Texture(_name, _sampler, _internalformat, _format)
{
    bind();
    parse_internalformat(mipmaps[0][0]->component, mipmaps[0][0]->type);
    parse_format(mipmaps[0][0]->component);
    sampler->tex_parameter(get_target());
    if (mipmap && mipmaps.size() > 1)
    {
        tex_Image(false);
        glGenerateMipmap(get_target());
        tex_Image(true);
    }
    else if (mipmap)
    {
        tex_Image(true);
        glGenerateMipmap(get_target());
    }
    else
    {
        tex_Image(true);
    }
}
Texture2DArray::Texture2DArray(std::vector<std::shared_ptr<Image>> images, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : Texture2DArray(std::vector<std::vector<std::shared_ptr<Image>>>(1, images), _name, _sampler, mipmap, _internalformat, _format, _border) {}
Texture2DArray::Texture2DArray(unsigned int type, int x, int y, int component, int levels, int depth, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat, GLenum _format, GLint _border) : border(_border), Texture(_name, _sampler, _internalformat, _format)
{
    mipmaps.resize(levels);
    for (int mip = 0; mip < levels; mip++) 
    {
        for (int d = 0; d < depth; d++)
        {
            mipmaps[mip].push_back(std::make_shared<Image>(type, x*std::pow(0.5, mip), y*std::pow(0.5, mip), component, nullptr));
        }
    }
    bind();
    sampler->tex_parameter(get_target());
    parse_internalformat(component, type);
    parse_format(component);
    tex_Image(false);
    if (mipmap)
    {
        glGenerateMipmap(get_target());
    }
}
void Texture2DArray::tex_Image(bool wirte_pixels, GLint level)
{
    std::shared_ptr<Image> image = mipmaps[level][0];
    int depth = mipmaps[level].size();
    char* buf = nullptr;
    if (wirte_pixels)
    {
        int img_len = image->x * image->y * image->component * (image->type == GL_UNSIGNED_BYTE ? sizeof(unsigned char) : sizeof(float));
        buf = (char*)malloc(depth * img_len);
        for (int i = 0; i < depth; i++)
        {
            memcpy(buf + i * img_len, mipmaps[level][i]->data, img_len);
        }
    }
    glTexImage3D(GL_TEXTURE_2D_ARRAY, level, internalformat, image->x, image->y, depth, border, format, image->type, buf);
    if (buf)
    {
        std::free(buf);
    }
}
void Texture2DArray::tex_Image(bool wirte_pixels)
{
    for (int i = 0; i < mipmaps.size(); i++)
    {
        tex_Image(wirte_pixels, i);
    }
}
GLenum Texture2DArray::get_target()
{
    return GL_TEXTURE_2D_ARRAY;
}