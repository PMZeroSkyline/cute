#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "shape.h"
#include "scene_graph/node.h"

struct Geometry
{
    // shape or mesh_node
    std::shared_ptr<Shape> shape;
    bool convexHull = false;
    Node* node = nullptr;
    Geometry(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const vec3& local_scale);
};

#endif