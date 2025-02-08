#include "mesh_gpu_instancing.h"
#include "scene_graph/transform.h"

MeshGPUInstancing::MeshGPUInstancing(const json &j, const json& gltf, const std::string &dir, Mesh* mesh)
{
    json attributes = j["attributes"];
    json accessor = gltf["accessors"][int(attributes["TRANSLATION"])];
    if (!gltf_access(dir, gltf, accessor, &TRANSLATION, nullptr))
        std::cout << "failed to read mesh instancing" << std::endl;
    accessor = gltf["accessors"][int(attributes["ROTATION"])];
    if (!gltf_access(dir, gltf, accessor, &ROTATION, nullptr))
        std::cout << "failed to read mesh instancing" << std::endl;
    accessor = gltf["accessors"][int(attributes["SCALE"])];
    if (!gltf_access(dir, gltf, accessor, &SCALE, nullptr))
        std::cout << "failed to read mesh instancing" << std::endl;
    update(mesh);
}
void MeshGPUInstancing::array_buffer_data(GLenum usage)
{
    std::vector<mat4> matrices;
    matrices.reserve(TRANSLATION.size());
    for (int i = 0; i < TRANSLATION.size(); i++)
        matrices.push_back(Transform(TRANSLATION[i], ROTATION[i], SCALE[i]).to_matrix());
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(mat4), &matrices[0], GL_STATIC_DRAW);
}
void MeshGPUInstancing::vertex_attrib()
{
    glEnableVertexAttribArray(10); 
    glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(vec4), (void*)0);
    glEnableVertexAttribArray(11); 
    glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(vec4), (void*)(1 * sizeof(vec4)));
    glEnableVertexAttribArray(12); 
    glVertexAttribPointer(12, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(vec4), (void*)(2 * sizeof(vec4)));
    glEnableVertexAttribArray(13); 
    glVertexAttribPointer(13, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(vec4), (void*)(3 * sizeof(vec4)));
    glVertexAttribDivisor(10, 1);
    glVertexAttribDivisor(11, 1);
    glVertexAttribDivisor(12, 1);
    glVertexAttribDivisor(13, 1);
}
void MeshGPUInstancing::update(Mesh* mesh)
{
    array_buffer = std::make_shared<Buffer>(GL_ARRAY_BUFFER);
    array_buffer->bind();
    array_buffer_data(GL_STATIC_DRAW);
    for (const auto& primitive : mesh->primitives)
    {
        primitive->vertex_array->bind();
        vertex_attrib();
    }
    vec3 _min, _max;
    bool first = true;
    for (int i = 0; i < TRANSLATION.size(); i++)
    {
        const mat4 M = Transform(TRANSLATION[i], ROTATION[i], SCALE[i]).to_matrix();
        for (const auto& primitive : mesh->primitives)
        {
            AABB b = M * (*primitive->attributes->bbox);
            _min = first ? b.get_min() : min(_min, b.get_min());
            _max = first ? b.get_max() : min(_max, b.get_max());
            if (first) first = false;
        }
    }
    bbox = AABB::make(_min, _max);
}