#ifndef MESH_GPU_INSTANCING_H
#define MESH_GPU_INSTANCING_H

#include "mesh.h"

struct MeshGPUInstancing
{
    // https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md
    std::vector<vec3> TRANSLATION;
    std::vector<quat> ROTATION;
    std::vector<vec3> SCALE;
    std::shared_ptr<Buffer> array_buffer;
    std::shared_ptr<AABB> bbox;
    MeshGPUInstancing(const json &j, const json& gltf, const std::string &dir, Mesh* mesh);
    void submit_array_buffer(GLenum usage);
    void submit_vertex_attrib();
    void submit(Mesh* mesh);
};

#endif