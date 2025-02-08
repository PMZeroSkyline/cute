#ifndef TEXTURE_CUBE_H
#define TEXTURE_CUBE_H

#include "texture.h"
#include "resource/image.h"
#include "core/math/quat.h"

struct TextureCube : Texture
{
    std::vector<std::array<std::shared_ptr<Image>, 6>> mipmaps;
    GLint border = 0;
    TextureCube(std::vector<std::array<std::shared_ptr<Image>, 6>> _mipmaps, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    TextureCube(std::array<std::shared_ptr<Image>, 6> faces, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    TextureCube(unsigned int type, int size, int component, int levels, const std::string& _name, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    void tex_image(bool wirtePixels, GLint level);
    void tex_image(bool wirtePixels);
    GLenum get_target() override;
    static std::array<quat, 6> orientations();
    static inline std::unordered_map<std::string, std::weak_ptr<TextureCube>> weak;
    static std::shared_ptr<TextureCube> get(const std::string& uris, bool flip_v, std::shared_ptr<TextureSampler> _sampler, bool mipmap, GLint _internalformat = 0, GLenum _format = 0, GLint _border = 0);
    static std::shared_ptr<TextureCube> make_test(int size, bool mipmap);
    static std::shared_ptr<TextureCube> make_color(int size, u8vec4 color, bool mipmap);
};

#endif