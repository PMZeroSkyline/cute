#ifndef IMAGE_H
#define IMAGE_H

#include "platform/graphics_wrapper/gl/gl_validation.h"
#include <string>
#include <unordered_map>
#include "core/math/vec2.h"
#include "core/math/vec4.h"
struct Image
{
    // regular texture need be flipped (to match opengl sample order) not flip cubemap (has been flipped https://www.khronos.org/opengl/wiki/Cubemap_Texture)
    unsigned int type = GL_FALSE;
    int x = 0, y = 0, component = 0;
    void *data = nullptr;
    std::string name;
    std::string path;
    Image() = default;
    Image(const std::string &_path, bool flip_v);
    Image(unsigned int _type, int _x, int _y, int _component, void* _data);
    Image(int _x, int _y, u8vec4 color);
    Image(int _x, int _y, vec4 color);
    int size();
    void alloc();
    void save(const std::string& _path, bool flip_v);
    ~Image();
    static void flip_vertical(void* dst, void* src, unsigned int type, int x, int y, int component);
    void flip_vertical();
    static void flip_horizontal(void* dst, void* src, int x, int y, int component);
    static void flip_horizontalf(void* dst, void* src, int x, int y, int component);
    static void flip_horizontal(void* dst, void* src, unsigned int type, int x, int y, int component);
    void flip_horizontal();
    void resize(ivec2 size);
    void* operator()(int _x, int _y);
    static inline std::unordered_map<std::string, std::weak_ptr<Image>> weak;
    static std::shared_ptr<Image> get(const std::string& _path, bool flip_v, bool resize_pwer_of_two);
};

#endif