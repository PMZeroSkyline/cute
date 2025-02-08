#ifndef AABB_H
#define AABB_H

#include "core/math/vec3.h"
#include "core/math/mat4.h"
#include <memory>

struct AABB
{
	vec3 center;
	vec3 extent;
	AABB() = default;
    AABB(const vec3& _center, const vec3& _extent);
	static AABB construct(const vec3& _min, const vec3& _max);
    static std::shared_ptr<AABB> make(const vec3& _min, const vec3& _max);
    vec3 get_min() const;
    vec3 get_max() const;
	float signed_distance(const vec3& point) const;
};
AABB operator*(const mat4 &M, const AABB& bbox);
#endif