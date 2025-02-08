#include "geometry.h"
#include "convex_hull_shape.h"
#include "mesh_shape.h"
#include "sphere_shape.h"
#include "box_shape.h"
#include "core/object_handle/get_or_make.h"

Geometry::Geometry(const json& j, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<Node>>& nodes, const vec3& local_scale)
{
    if (j.contains("convexHull"))
    {
        convexHull = j["convexHull"];
    }
    if (j.contains("node"))
    {
        std::shared_ptr<Node> n = nodes[j["node"]];
        if (convexHull)
        {
            shape = get_or_make(ConvexHullShape::weak, ConvexHullShape::hash(n->get_component<MeshComponent>()->mesh.get(), local_scale), [&n, &local_scale](){
                return std::make_shared<ConvexHullShape>(n, local_scale);
            });
        }
        else
        {
            shape = get_or_make(MeshShape::weak, MeshShape::hash(n->get_component<MeshComponent>()->mesh.get(), local_scale), [&n, &local_scale](){
                return std::make_shared<MeshShape>(n, local_scale);
            });
        }
        node = n.get();
    }
    else if (j.contains("shape"))
    {
        std::shared_ptr<Shape> _shape = shapes[j["shape"]];
        if (SphereShape* s = dynamic_cast<SphereShape*>(_shape.get()))
        {
            shape = get_or_make(SphereShape::weak, SphereShape::hash(s->radius, local_scale), [&s, &local_scale](){
                return std::make_shared<SphereShape>(s->radius, local_scale);
            });
        }
        else if (BoxShape* s = dynamic_cast<BoxShape*>(_shape.get()))
        {
            shape = get_or_make(BoxShape::weak, BoxShape::hash(s->size, local_scale), [&s, &local_scale](){
                return std::make_shared<BoxShape>(s->size, local_scale);
            });
        }
    }
}