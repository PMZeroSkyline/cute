#ifndef MESH_SHAPE_H
#define MESH_SHAPE_H

#include "shape.h"
#include "scene_graph/node.h"
#include "resource/mesh_component.h"

struct MeshShape : Shape
{
    std::shared_ptr<Node> node;
    std::shared_ptr<btTriangleMesh> bullet_triangle_mesh;
    MeshShape() = default;
    MeshShape(std::shared_ptr<Node> _node, const vec3& local_scale = vec3(1.f));
    MeshShape(std::shared_ptr<Node> _node, std::shared_ptr<btTriangleMesh> _bMesh);
    static size_t hash(Mesh* mesh, const vec3& local_scale);
    static inline std::unordered_map<size_t, std::weak_ptr<MeshShape>> weak;
};
template <>
struct std::hash<MeshShape> {
    size_t operator()(const MeshShape& s) const {
        return MeshShape::hash(s.node->get_component<MeshComponent>()->mesh.get(), *(vec3*)&s.bullet_shape->getLocalScaling());
    }
};
#endif