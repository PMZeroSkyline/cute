#include "gl_validation.h"

void gl_check_error_(const char *file, int line)
{
    GLenum code;
    while ((code = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (code)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
}
#if defined(GL_VALIDATION)
bool gl_check_framebuffer_complete_(const char *file, int line)
{
    if (glCheckFramebufferStatus_(GL_FRAMEBUFFER, file, line) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "glCheckFramebufferStatus != GL_FRAMEBUFFER_COMPLETE " << " | " << file << " (" << line << ")" << std::endl;
        return false;
    }
    return true;
}
#endif