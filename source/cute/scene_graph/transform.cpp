#include "transform.h"

Transform::Transform() : scale(1.f) {}
Transform::Transform(const vec3 t, const quat r, const vec3 s) : position(t), rotation(r), scale(s) {}
Transform::Transform(const mat4 &matrix)
{
    mat4::decompose(matrix, position, rotation, scale);
}
mat4 Transform::to_matrix() const
{
    return mat4::translate(position) * mat4(rotation) * mat3::scale(scale);
}
std::ostream &operator<<(std::ostream &os, const Transform &t)
{
	os << t.position << " " << degrees(vec3(t.rotation)) << " " << t.scale;
	return os;
}
