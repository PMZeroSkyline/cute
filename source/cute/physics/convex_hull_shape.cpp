#include "convex_hull_shape.h"

ConvexHullShape::ConvexHullShape(std::shared_ptr<Node> _node, const vec3& local_scale) : node(_node)
{
    Mesh* mesh = node->get_component<MeshComponent>()->mesh.get();
    if (mesh->primitives.size() == 1)
    {
        auto primitive = node->get_component<MeshComponent>()->mesh->primitives[0];
        bullet_shape = std::make_shared<btConvexHullShape>((const btScalar*)&primitive->attributes->POSITION[0], primitive->attributes->POSITION.size(), sizeof(vec3));
    }
    else
    {
        std::vector<vec3> positions;
        for (const auto& primitive : mesh->primitives)
        {
            positions.insert(positions.end(), primitive->attributes->POSITION.begin(), primitive->attributes->POSITION.end());
        }
        bullet_shape = std::make_shared<btConvexHullShape>((const btScalar*)&positions[0], positions.size(), sizeof(vec3));
    }
    bullet_shape->setLocalScaling(*(btVector3*)&local_scale);
}
size_t ConvexHullShape::hash(Mesh* mesh, const vec3& local_scale)
{
    size_t h1 = std::hash<void*>{}(mesh);
    size_t h2 = std::hash<vec3>{}(local_scale);
    return h1 ^ (h2 << 1);
}
template struct std::hash<ConvexHullShape>;