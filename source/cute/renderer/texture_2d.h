#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "texture.h"
#include "resource/image.h"

struct Texture2D : Texture
{
    std::vector<std::shared_ptr<Image>> mipmaps;
    GLint border = 0;
    Texture2D() = default;
    Texture2D(const std::vector<std::shared_ptr<Image>>& _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    Texture2D(const std::shared_ptr<Image>& image, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    Texture2D(unsigned int type, int x, int y, int component, int levels, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    void tex_image(bool wirte_pixels, GLint level);
    void tex_image(bool wirte_pixels);
    GLenum get_target() override;
    static inline std::unordered_map<std::string, std::weak_ptr<Texture2D>> weak;
    static std::shared_ptr<Texture2D> get(const std::string& path, bool flip_v, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0, bool resize_power_of_two = true);
};

#endif