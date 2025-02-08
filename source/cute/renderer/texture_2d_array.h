#ifndef TEXTURE_2D_ARRAY_H
#define TEXTURE_2D_ARRAY_H

#include "texture.h"
#include "resource/image.h"

struct Texture2DArray : Texture
{
    std::vector<std::vector<std::shared_ptr<Image>>> mipmaps;
    GLint border = 0;
    Texture2DArray(std::vector<std::vector<std::shared_ptr<Image>>> _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    Texture2DArray(std::vector<std::shared_ptr<Image>> images, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    Texture2DArray(unsigned int type, int x, int y, int component, int levels, int depth, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    void tex_Image(bool wirte_pixels, GLint level);
    void tex_Image(bool wirte_pixels);
    GLenum get_target() override;
};

#endif