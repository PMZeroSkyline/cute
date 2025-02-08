#include "plane.h"

Plane Plane::operator/(const float& s)
{
	return Plane(normal / s, distance / s);
}
Plane Plane::operator/(const float& s) const
{
	return Plane(normal / s, distance / s);
}
float Plane::signed_distance(const vec3& point) const
{
    // https://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
    return dot(point, normal) + distance;
}
float length(const Plane &p)
{
	return length(p.normal);
}
Plane normalize(const Plane &p)
{
    // https://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
	return p / length(p);
}