#include "frustum.h"

Frustum::Frustum(const mat4& /*P * V*/M)
{
    // https://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
    for (int i = 0; i < 3; i++)
    {
        planes[i * 2] = normalize(Plane(M.row(3) - M.row(i)));
        planes[i * 2 + 1] = normalize(Plane(M.row(3) + M.row(i)));
    }
}
bool Frustum::intersect(const AABB &bbox) const
{
    for (int i = 0; i < 6; i++)
    {
        const Plane &p = planes[i];
        if (p.signed_distance(bbox.center) < -dot(abs(p.normal), bbox.extent))
            return false;
    }
    return true;
}