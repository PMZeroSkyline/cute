#include "opengl_api.h"

OpenglAPI::OpenglAPI()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cout << "failed to initialize glad" << std::endl;
    }

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    ver = major * 100 + minor * 10;

    std::map<int, int> ver_map = {{200, 110}, {210, 120}, {300, 130}, {310, 140}, {320, 150}};
    std::map<int, int>::iterator it = ver_map.find(ver);
    if (it != ver_map.end()) 
    {
        lang_ver = it->second;
    }
    else 
    {
        lang_ver = ver;
    }
    
    if (lang_ver > 300 || ver > 300)
    {
        GLint exts = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &exts);
        for (GLint i = 0; i < exts; ++i) 
        {
            const char* ext = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
            extensions.insert(ext);
        }

        return;
    }

    if (!glGetString)
    {
        if (glfwExtensionSupported(GL_ARB_TEXTURE_FILTER_ANISOTROPIC_EXTENSION_NAME))
        {
            extensions.insert(GL_ARB_TEXTURE_FILTER_ANISOTROPIC_EXTENSION_NAME);
        }

        return;
    }

    const GLubyte *exts = glGetString(GL_EXTENSIONS);
    if (!exts)
    {
        return;
    }
    
    if (const char* str = reinterpret_cast<const char*>(exts))
    {
        std::istringstream ess(str);
        std::string ext;
        while (ess >> ext) 
        {
            extensions.insert(ext);
        }
    }
}
void OpenglAPI::swap_buffers()
{
    DesktopWindow* w = (DesktopWindow*)App::instance->window.get();
    glfwSwapBuffers(w->glfw_window);
}