#include "mesh_shape.h"

MeshShape::MeshShape(std::shared_ptr<Node> _node, const vec3& local_scale) : node(_node)
{
    Mesh* mesh = node->get_component<MeshComponent>()->mesh.get();
    bullet_triangle_mesh = std::make_unique<btTriangleMesh>();
    for (const auto& primitive : mesh->primitives)
    {
        for (int i = 0; i < primitive->indices->size() / 3; i++)
        {
            const btVector3& v0 = *(btVector3*)&primitive->attributes->POSITION[primitive->indices->at(i * 3)];
            const btVector3& v1 = *(btVector3*)&primitive->attributes->POSITION[primitive->indices->at(i * 3 + 1)];
            const btVector3& v2 = *(btVector3*)&primitive->attributes->POSITION[primitive->indices->at(i * 3 + 2)];
            bullet_triangle_mesh->addTriangle(v0, v1, v2);
        }
    }
    bullet_shape = std::make_shared<btBvhTriangleMeshShape>(bullet_triangle_mesh.get(), true, true);
    bullet_shape->setLocalScaling(*(btVector3*)&local_scale);
}
MeshShape::MeshShape(std::shared_ptr<Node> _node, std::shared_ptr<btTriangleMesh> _bMesh) : node(_node), bullet_triangle_mesh(_bMesh)
{
    bullet_shape = std::make_shared<btBvhTriangleMeshShape>(bullet_triangle_mesh.get(), true, true);
}
size_t MeshShape::hash(Mesh* mesh, const vec3& local_scale)
{
    size_t h1 = std::hash<void*>{}(mesh);
    size_t h2 = std::hash<vec3>{}(local_scale);
    return h1 ^ (h2 << 1);
}
template struct std::hash<MeshShape>;