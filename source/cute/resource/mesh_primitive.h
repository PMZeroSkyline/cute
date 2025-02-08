#ifndef MESH_PRIMITIVE_H
#define MESH_PRIMITIVE_H

#include "mesh_primitive_attributes.h"
#include "mesh_primitive_target.h"
#include "material.h"
#include "platform/graphics_wrapper/buffer.h"
#include "platform/graphics_wrapper/vertex_array.h"

struct MeshPrimitive
{
    std::shared_ptr<MeshPrimitiveAttributes> attributes;
    std::shared_ptr<std::vector<unsigned int>> indices;
    std::shared_ptr<Material> material;
    std::shared_ptr<std::vector<MeshPrimitiveTarget>> targets;
    std::shared_ptr<VertexArray> vertex_array;
    std::shared_ptr<Buffer> array_buffer;
    std::shared_ptr<Buffer> element_array_buffer;
    MeshPrimitive() = default;
    MeshPrimitive(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Material>>& materials);
    void update(std::vector<float>* weights);
    void array_buffer_data(GLenum usage, std::vector<float>* weights) const; 
    void vertex_attrib() const; 
    void element_buffer_data(GLenum usage) const;
    static std::shared_ptr<MeshPrimitive> make_plane();
    static std::shared_ptr<MeshPrimitive> make_cube();
    static std::shared_ptr<MeshPrimitive> make_sphere(int phi_slice, int theta_slice);
    static inline std::unordered_map<std::string, std::weak_ptr<MeshPrimitive>> weak;
    static std::shared_ptr<MeshPrimitive> get_plane();  
};


#endif