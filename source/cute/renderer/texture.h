#ifndef TEXTURE_H
#define TEXTURE_H

#include "texture_sampler.h"

struct Texture
{
    GLuint id = -1;
    std::string name;
    std::shared_ptr<TextureSampler> sampler;
    GLint internalformat = 0;
    GLenum format = 0;
    Texture() = default;
    Texture(std::string _name, std::shared_ptr<TextureSampler> _sampler, GLint _internalformat, GLenum _format);
    virtual GLenum get_target() = 0;
    virtual ~Texture();
    void bind();
    void parse_internalformat(int channel, unsigned int type);
    void parse_format(int channel);
};

#endif