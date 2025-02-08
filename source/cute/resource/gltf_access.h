#ifndef GLTF_ACCESS_H
#define GLTF_ACCESS_H

#include "core/parser/json.h"
#include "platform/graphics_wrapper/gl_validation.h"
#include "core/math/vec2.h"
#include "core/math/vec4.h"
#include "core/math/quat.h"

template<typename T>
bool gltf_view_buffer(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<T>* dst)
{
    json buffer_view = gltf["bufferViews"][buffer_view_id];
    json buffer = gltf["buffers"][int(buffer_view["buffer"])];
    FILE *fp = fopen((dir + "/" + std::string(buffer["uri"])).c_str(), "rb");
    if (fp)
    {
        fseek(fp, byte_offset + buffer_view.value("byteOffset", 0), SEEK_SET);
        dst->resize(count);
        fread(&(*dst)[0], sizeof(T), count, fp);
        fclose(fp);
        return true;
    }
    return false;
}
template<typename C, typename T>
bool gltf_view_buffer_cast(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<T>* dst)
{
    json buffer_view = gltf["bufferViews"][buffer_view_id];
    json buffer = gltf["buffers"][int(buffer_view["buffer"])];
    FILE *fp = fopen((dir + "/" + std::string(buffer["uri"])).c_str(), "rb");
    if (fp)
    {
        fseek(fp, byte_offset + buffer_view.value("byteOffset", 0), SEEK_SET);
        std::vector<C> convert;
        convert.resize(count);
        fread(&convert[0], sizeof(C), count, fp);
        fclose(fp);
        (*dst) = std::vector<T>(convert.begin(), convert.end());
        return true;
    }
    return false;
}
template<typename T>
bool gltf_access(const std::string& dir, const json& gltf, const json& accessor, int buffer_view_id, int byte_offset, int count, std::vector<T>* dst)
{
    if (typeid(T) == typeid(unsigned int))
    {
        if (accessor["type"] != "SCALAR")
        {
            return false;
        }
        if (accessor["componentType"] == GL_UNSIGNED_INT)
        {
            return gltf_view_buffer(dir, gltf, buffer_view_id, byte_offset, count, dst);
        }
        else if (accessor["componentType"] == GL_UNSIGNED_SHORT)
        {
            return gltf_view_buffer_cast<unsigned short>(dir, gltf, buffer_view_id, byte_offset, count, (std::vector<unsigned int>*)dst);
        }
    }
    else if (typeid(T) == typeid(vec2))
    {
        if (accessor["type"] != "VEC2")
        {
            return false;
        }
        if (accessor["componentType"] == GL_FLOAT)
        {
            return gltf_view_buffer(dir, gltf, buffer_view_id, byte_offset, count, dst);
        }
    }
    else if (typeid(T) == typeid(vec3))
    {
        if (accessor["type"] != "VEC3")
        {
            return false;
        }
        if (accessor["componentType"] == GL_FLOAT)
        {
            return gltf_view_buffer(dir, gltf, buffer_view_id, byte_offset, count, dst);
        }
    }
    else if (typeid(T) == typeid(vec4))
    {
        if (accessor["type"] != "VEC4")
        {
            return false;
        }
        if (accessor["componentType"] == GL_FLOAT)
        {
            return gltf_view_buffer(dir, gltf, buffer_view_id, byte_offset, count, dst);
        }
        else if (accessor["componentType"] == GL_UNSIGNED_BYTE)
        {
            return gltf_view_buffer_cast<u8vec4>(dir, gltf, buffer_view_id, byte_offset, count, (std::vector<vec4>*)dst);
        }
    }
    else if (typeid(T) == typeid(quat))
    {
        if (accessor["type"] != "VEC4")
        {
            return false;
        }
        if (accessor["componentType"] == GL_FLOAT)
        {
            return gltf_view_buffer(dir, gltf, buffer_view_id, byte_offset, count, dst);
        }
    }
    return false;
}
template<typename T>
bool gltf_access(const std::string& dir, const json& gltf, const json& accessor, std::vector<T>* dst, std::vector<unsigned int>* sparse_indices)
{
    int byte_offset = accessor.value("byteOffset", 0);
    int buffer_view;
    int count;
    if (accessor.contains("sparse"))
    {
        json sparse = accessor["sparse"];
        json indices = sparse["indices"];
        json values = sparse["values"];
        buffer_view = indices["bufferView"];
        count = sparse["count"];
        if (indices["componentType"] == GL_UNSIGNED_INT)
        {
            if (!gltf_view_buffer(dir, gltf, buffer_view, byte_offset, count, sparse_indices)) return false;
        }
        else if (indices["componentType"] == GL_UNSIGNED_SHORT)
        {
            if (!gltf_view_buffer_cast<unsigned short>(dir, gltf, buffer_view, byte_offset, count, (std::vector<unsigned int>*)sparse_indices)) return false;
        }
    }
    else
    {
        buffer_view = accessor["bufferView"];
        count = accessor["count"];
    }
    return gltf_access(dir, gltf, accessor, buffer_view, byte_offset, count, dst);
}
#endif