#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "plane.h"
#include "aabb.h"
#include "mat4.h"

struct Frustum
{	
	Plane planes[6]; // Right,Left,Top,Bottom,Far,Near
	Frustum() = default;
	Frustum(const mat4& /*P * V*/M);
    bool intersect(const AABB &bbox) const;
};

#endif