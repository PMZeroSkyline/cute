#ifndef CONVEX_HULL_SHAPE_H
#define CONVEX_HULL_SHAPE_H

#include "shape.h"
#include "scene_graph/node.h"
#include "resource/mesh_component.h"

struct ConvexHullShape : Shape
{
    std::shared_ptr<Node> node;
    ConvexHullShape(std::shared_ptr<Node> _node, const vec3& local_scale = vec3(1.f));
    static size_t hash(Mesh* mesh, const vec3& local_scale);
    static inline std::unordered_map<size_t, std::weak_ptr<ConvexHullShape>> weak;
};
template <>
struct std::hash<ConvexHullShape> {
    size_t operator()(const ConvexHullShape& s) const {
        return ConvexHullShape::hash(s.node->get_component<MeshComponent>()->mesh.get(), *(vec3*)&s.bullet_shape->getLocalScaling());
    }
};
#endif