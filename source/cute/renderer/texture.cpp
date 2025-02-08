#include "texture.h"

Texture::Texture(std::string _name, std::shared_ptr<TextureSampler> _sampler, GLint _internalformat, GLenum _format) : name(_name), sampler(_sampler), internalformat(_internalformat), format(_format)
{
    glGenTextures(1, &id);
}
Texture::~Texture()
{
    glDeleteTextures(1, &id);
}
void Texture::bind()
{
    glBindTexture(get_target(), id);
}
void Texture::parse_internalformat(int channel, unsigned int type)
{
    if (internalformat == 0)
    {
        if (type == GL_FLOAT)
        {
            switch (channel) {
            case 1: internalformat = GL_R32F; break;
            case 2: internalformat = GL_RG32F; break;
            case 3: internalformat = GL_RGB32F; break;
            case 4: internalformat = GL_RGBA32F; break;
            case GL_DEPTH_STENCIL: internalformat = GL_DEPTH24_STENCIL8; break;
            case GL_DEPTH_COMPONENT: internalformat = GL_DEPTH_COMPONENT32F; break;
            default: std::cout << "can't to find GL_FLOAT image internalformat" << std::endl; break;
            }
        }
        else if (type == GL_HALF_FLOAT)
        {
            switch (channel) {
            case 1: internalformat = GL_R16F; break;
            case 2: internalformat = GL_RG16F; break;
            case 3: internalformat = GL_RGB16F; break;
            case 4: internalformat = GL_RGBA16F; break;
            default: std::cout << "can't to find GL_HALF_FLOAT image internalformat" << std::endl; break;
            }
        }
        else if (type == GL_UNSIGNED_BYTE)
        {
            switch (channel) {
            case 1: internalformat = GL_R8; break;
            case 2: internalformat = GL_RG8; break;
            case 3: internalformat = GL_RGB8; break;
            case 4: internalformat = GL_RGBA8; break;
            default: std::cout << "can't to find GL_UNSGINED_BYTE image internalformat" << std::endl; break;
            }
        }
        else
        {
            std::cout << "can't to find image internalformat" << channel << " " << type << std::endl;
        }
    }
}
void Texture::parse_format(int channel)
{
    if (format == 0)
    {
        switch (channel) {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        case GL_DEPTH_STENCIL: format = GL_DEPTH_STENCIL; break;
        case GL_DEPTH_COMPONENT: format = GL_DEPTH_COMPONENT; break;
        default: std::cout << "can't to find image format" << std::endl; break;
        }
    }
}