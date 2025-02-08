#include "image.h"
#include <iostream>
#include "core/object_handle/get_or_make.h"
#include "core/math/power_of_two.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(const std::string &_path, bool flip_v) : path(_path)
{
    if (data)
    {
        stbi_image_free(data);
        data = nullptr;
    }
    stbi_set_flip_vertically_on_load(flip_v);
    if (path.substr(path.find_last_of(".")) == ".hdr")
    {
        data = (void*)stbi_loadf(path.c_str(), &x, &y, &component, 0);
        if (!data)
        {
            std::cout << "failed to load hdr Image " << path << std::endl;
            return;
        }
        type = GL_FLOAT;
    }
    else
    {
        data = stbi_load(path.c_str(), &x, &y, &component, 0);
        if (!data)
        {
            std::cout << "failed to load Image " << path << std::endl;
            return;
        }
        type = GL_UNSIGNED_BYTE;
    }
}
Image::Image(unsigned int _type, int _x, int _y, int _component, void* _data) : type(_type), x(_x), y(_y), component(_component), data(_data) {}
Image::Image(int _x, int _y, u8vec4 color) : type(GL_UNSIGNED_BYTE), x(_x), y(_y), component(4)
{
    alloc();
    for (int _y = 0; _y < y; _y++)
    {
        for (int _x = 0; _x < x; _x++)
        {
            *(u8vec4*)(*this)(_x, _y) = color;
        }
    }
}
Image::Image(int _x, int _y, vec4 color) : type(GL_FLOAT), x(_x), y(_y), component(4)
{
    alloc();
    for (int _y = 0; _y < y; _y++)
    {
        for (int _x = 0; _x < x; _x++)
        {
            *(vec4*)(*this)(_x, _y) = color;
        }
    }
}
int Image::size()
{
    return x * y * component * (type == GL_FLOAT ? sizeof(float) : sizeof(stbi_uc));
}
void Image::alloc()
{
    if (data)
    {
        stbi_image_free(data);
    }
    if (!size())
    {
        data = nullptr;
        return;
    }
    data = malloc(size());
}
void Image::save(const std::string& _path, bool flip_v)
{
    if (data == nullptr)
    {
        return;
    }
    void* flip_data = nullptr;
    if (flip_v)
    {
        flip_data = malloc(size());
        Image::flip_vertical(flip_data, data, type, x, y, component);
    }
    std::string ext = _path.substr(_path.find_last_of("."));
    if (ext == ".hdr")
    {
        if (stbi_write_hdr(_path.c_str(), x, y, component, (float*)(flip_v ? flip_data : data)))
        {
            std::cout << "failed to save " << _path << std::endl;
        }
    }
    else if (ext == ".png")
    {
        if (stbi_write_png(_path.c_str(), x, y, component, flip_v ? flip_data : data, x * component))
        {
            std::cout << "failed to save " << _path << std::endl;
        }
    }
    else if (ext == ".jpg")
    {
        if (stbi_write_jpg(_path.c_str(), x, y, component, flip_v ? flip_data : data, 100))
        {
            std::cout << "failed to save " << _path << std::endl;
        }
    }
    if (flip_data)
    {
        stbi_image_free(flip_data);
    }
}
Image::~Image()
{
    if (data)
    {
        stbi_image_free(data);
    }
}
void Image::flip_vertical(void* dst, void* src, unsigned int type, int x, int y, int component)
{
    int row_len = x * component * (type == GL_FLOAT ? sizeof(float) : sizeof(stbi_uc));
    for (int i = 0; i < y / 2; ++i) 
    {
        void* src_row_start = (char*)src + i * row_len;
        void* src_row_opposite = (char*)src + (y - 1 - i) * row_len;
        void* dst_row_start = (char*)dst + i * row_len;
        void* dst_row_opposite = (char*)dst + (y - 1 - i) * row_len;
        std::memcpy(dst_row_opposite, src_row_start, row_len);
        std::memcpy(dst_row_start, src_row_opposite, row_len);
    }
}
void Image::flip_vertical()
{
    if (data == nullptr) {
        return;
    }
    void* buffer = malloc(size());
    Image::flip_vertical(buffer, data, type, x, y, component);
    stbi_image_free(data);
    data = buffer;
}
void Image::flip_horizontal(void* dst, void* src, int x, int y, int component)
{
    int color_len = component * sizeof(stbi_uc);
    int row_len = x * color_len;
    for (int i = 0; i < y; ++i) 
    {
        stbi_uc* src_row_start = (stbi_uc*)src + i * row_len;
        stbi_uc* dst_row_start = (stbi_uc*)dst + i * row_len;
        for (int j = 0; j < x / 2; ++j) 
        {
            stbi_uc* src_start = src_row_start + j * color_len;
            stbi_uc* src_opposite = src_row_start + (x - 1 - j) * color_len;
            stbi_uc* dst_start = dst_row_start + j * color_len;
            stbi_uc* dst_opposite = dst_row_start + (x - 1 - j) * color_len;
            std::memcpy(dst_start, src_opposite, color_len);
            std::memcpy(dst_opposite, src_start, color_len);
        }
    }
}
void Image::flip_horizontalf(void* dst, void* src, int x, int y, int component)
{
    int color_len = component * sizeof(float);
    int row_len = x * color_len;
    for (int i = 0; i < y; ++i) 
    {
        float* src_row_start = (float*)src + i * row_len;
        float* dst_row_start = (float*)dst + i * row_len;
        for (int j = 0; j < x / 2; ++j) 
        {
            float* src_start = src_row_start + j * color_len;
            float* src_opposite = src_row_start + (x - 1 - j) * color_len;
            float* dst_start = dst_row_start + j * color_len;
            float* dst_opposite = dst_row_start + (x - 1 - j) * color_len;
            std::memcpy(dst_start, src_opposite, color_len);
            std::memcpy(dst_opposite, src_start, color_len);
        }
    }
}
void Image::flip_horizontal(void* dst, void* src, unsigned int type, int x, int y, int component)
{
    if (type == GL_UNSIGNED_BYTE)
    {
        flip_horizontal(dst, src, x, y, component);
    }
    else if (type == GL_FLOAT)
    {
        
        flip_horizontalf(dst, src, x, y, component);
    }
}
void Image::flip_horizontal()
{
    if (data == nullptr)
    {
        return;
    }
    void* buffer = malloc(size());
    Image::flip_horizontal(buffer, data, type, x, y, component);
    stbi_image_free(data);
    data = buffer;
}
void Image::resize(ivec2 size)
{
    if (data == nullptr) 
    {
        return;
    }
    if (type == GL_UNSIGNED_BYTE)
    {
        void *buffer = malloc(size.x * size.y * component * sizeof(stbi_uc));
        stbir_resize_uint8((stbi_uc *)data, x, y, 0, (stbi_uc *)buffer, size.x, size.y, 0, component);
        stbi_image_free(data);
        data = buffer;
        x = size.x;
        y = size.y;
    }
    else if (type == GL_FLOAT)
    {
        void *buffer = malloc(size.x * size.y * component * sizeof(float));
        stbir_resize_float((float *)data, x, y, 0, (float *)buffer, size.x, size.y, 0, component);
        stbi_image_free(data);
        data = buffer;
        x = size.x;
        y = size.y;
    }
    else
    {
        std::cout << "failed to resize image, type not support !" << std::endl;
    }
}
void* Image::operator()(int _x, int _y) 
{
    return ((char*)data) + (_y * x + _x) * (type == GL_UNSIGNED_BYTE ? sizeof(stbi_uc) : sizeof(float)) * component;
}
std::shared_ptr<Image> Image::get(const std::string& _path, bool flip_v, bool resize_pwer_of_two)
{
    return get_or_make(weak, _path, [&_path, &flip_v, &resize_pwer_of_two](){
        std::shared_ptr<Image> img = std::make_shared<Image>(_path, flip_v);
        if (resize_pwer_of_two && (!is_pow_of_two(img->x) || !is_pow_of_two(img->y)))
        {
            img->resize(ivec2(round_pow_of_two(img->x), round_pow_of_two(img->y)));
        }
        return img;
    });
}