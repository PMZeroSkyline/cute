#ifndef BUFFER_H
#define BUFFER_H

#include "platform/graphics_wrapper/gl_validation.h"
#include <unordered_map>
#include <memory>
#include <string>

struct Buffer
{
    GLuint id = -1;
    GLenum target = GL_FALSE;
    Buffer(GLenum _target);
    virtual ~Buffer();
    void bind();
    static inline std::unordered_map<std::string, GLuint> binding;
    static inline std::unordered_map<std::string, std::shared_ptr<Buffer>> shared;
    template<typename T>
    static std::shared_ptr<Buffer> make_uniform(const std::string& name, int base)
    {
        std::shared_ptr<Buffer> buf = std::make_shared<Buffer>(GL_UNIFORM_BUFFER);
		buf->bind();
        glBufferData(GL_UNIFORM_BUFFER, sizeof(T), NULL, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, base, buf->id);
        Buffer::binding[name] = base;
        Buffer::shared[name] = buf;
        return buf;
    }
    template<typename T>
    static std::shared_ptr<Buffer> get_uniform(const std::string& name)
    {
        if (binding.count(name))
        {
            return shared[name];
        }
        if (binding.size())
        {
            GLuint point = 0;
            for (const auto& pair : binding)
            {
                if (pair.second > point)
                {
                    point = pair.second;
                }
            }
            return make_uniform<T>(name, ++point);
        }
        return make_uniform<T>(name, 0);
    }
};

#endif