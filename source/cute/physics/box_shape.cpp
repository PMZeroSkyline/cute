#include "box_shape.h"

BoxShape::BoxShape(const vec3& _size, const vec3& local_scale) : size(_size)
{
    bullet_shape = std::make_shared<btBoxShape>((size * .5f).bullet());
    bullet_shape->setLocalScaling(*(btVector3*)&local_scale);
}
BoxShape::BoxShape(const json& j) : BoxShape(*(vec3*)j["size"].get<std::array<float, 3>>().data()) {}
size_t BoxShape::hash(const vec3& _size, const vec3& local_scale)
{
    size_t h1 = std::hash<vec3>{}(_size);
    size_t h2 = std::hash<vec3>{}(local_scale);
    return h1 ^ (h2 << 1);
}