#ifndef QUAT_H
#define QUAT_H

#include "common.h"
#include "vec4.h"

template <typename T>
struct mat3t;

template <typename T>
struct quatt
{
	T x, y, z, w;
	quatt() : x(0), y(0), z(0), w(1) {}
	quatt(T i) : x(i), y(i), z(i), w(i) {}
	quatt(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	template <typename U>
	quatt(const quatt<U> &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    quatt(const mat3t<T> &m);
	quatt(const vec3t<T> &in_euler)
	{
		// Euler angles (in 3-2-1 sequence) to quaternion conversion
		// https://en.wikipedia.org/wiki/Conversion_between_quats_and_Euler_angles
		vec3t<T> euler = (in_euler);
		T pitch = euler.y;
		T yaw = euler.z;
		T roll = euler.x;
		T cr = cos(roll * 0.5);
		T sr = sin(roll * 0.5);
		T cp = cos(pitch * 0.5);
		T sp = sin(pitch * 0.5);
		T cy = cos(yaw * 0.5);
		T sy = sin(yaw * 0.5);
		w = cr * cp * cy + sr * sp * sy;
		x = sr * cp * cy - cr * sp * sy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
	}
	// quatt(const mat3t<T> &m);
	quatt(const T &angle, const vec3t<T> &v) // angleAxis
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
		const T halfAngle = angle * 0.5;
		const T s = sin(halfAngle);
		x = v.x * s;
		y = v.y * s;
		z = v.z * s;
		w = cos(halfAngle);
	}
	quatt(const vec3t<T> &orig, vec3t<T> const &dest) // rotation
	{
		T cosTheta = dot(orig, dest);
		vec3t<T> rotationAxis;
		if (cosTheta >= 1 - std::numeric_limits<T>::epsilon())
		{
			*this = quatt<T>();
			return;
		}
		if (cosTheta < -1 + std::numeric_limits<T>::epsilon())
		{
			rotationAxis = cross(vec3t<T>(0, 0, 1), orig);
			if (dot(rotationAxis, rotationAxis) < std::numeric_limits<T>::epsilon())
			{
				rotationAxis = cross(vec3t<T>(1, 0, 0), orig);
			}
			rotationAxis = normalize(rotationAxis);
			*this = quatt<T>(T(PI), rotationAxis);
			return;
		}
		rotationAxis = cross(orig, dest);
		T s = sqrt((T(1) + cosTheta) * 2);
		T invs = 1 / s;
		x = rotationAxis.x * invs;
		y = rotationAxis.y * invs;
		z = rotationAxis.z * invs;
		w = s * 0.5f;
	}
	quatt operator+(const quatt &v) const
	{
		return quatt(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	quatt operator+=(const quatt &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	quatt operator-(const quatt &v) const
	{
		return quatt(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	quatt operator-=(const quatt &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	quatt operator*(T v) const
	{
		return quatt(x * v, y * v, z * v, w * v);
	}
	quatt operator*(const quatt &v) const
	{
		const quatt p(*this);
		const quatt q(v);
		quatt r;
		r.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		r.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		r.y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		r.z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return r;
	}
	vec3t<T> operator*(const vec3t<T> &v) const
	{
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		vec3t<T> qv = vec3t<T>(x, y, z);
		vec3t<T> t = cross(qv * 2, v);
		return v + t * w + cross(qv, t);
	}
	quatt operator*=(const quatt &v)
	{
		const quatt p(*this);
		const quatt q(v);
		w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return *this;
	}
	quatt operator/(T v) const
	{
		return quatt(x / v, y / v, z / v, w / v);
	}
	quatt operator/(const quatt &v) const
	{
		return quatt(x / v.x, y / v.y, z / v.z, w / v.w);
	}
	quatt operator/=(const quatt &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
	bool operator==(const quatt &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	}
	bool operator!=(const quatt &v) const
	{
		return !(*this == v);
	}
	T &operator[](int i)
	{
		return *((T *)this + i);
	}
	T const &operator[](int i) const
	{
		return *((T *)this + i);
	}
	quatt operator-() const
	{
		return quatt(-((float)x), -((float)y), -((float)z), -((float)w));
	}
	friend T length(const quatt &q)
	{
		return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	}
	friend quatt normalize(const quatt &q)
	{
		T len = length(q);
		if (len > 0)
		{
			return q / len;
		}
		else
		{
			return quatt();
		}
	}
	friend quatt inverse(const quatt &q)
	{
		T norm = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
		quatt invQ;
		invQ.w = q.w / norm;
		invQ.x = -q.x / norm;
		invQ.y = -q.y / norm;
		invQ.z = -q.z / norm;
		return invQ;
	}
	friend std::ostream &operator<<(std::ostream &os, const quatt &v)
	{
		for (int i = 0; i < 4; i++)
		{
			T value = v[i];
			if (std::abs((float)value) <= std::numeric_limits<T>::epsilon())
			{
				value = 0;
			}
			os << value << " ";
		}
		return os;
	}
	#ifdef INCLUDE_NLOHMANN_JSON_HPP_
	friend void to_json(json& j, const quatt& q) 
	{
		j[0] = q.x;
		j[1] = q.y;
		j[2] = q.z;
		j[3] = q.w;
	}
	friend void from_json(const json& j, quatt& q) 
	{
		q = *(quatt*)j.get<std::array<T, 4>>().data();
	}
	#endif
	#ifdef BT_VECTOR3_H
	btQuaternion bullet() 
	{
		return btQuaternion(x, y, z, w);
	}
	quatt(const btQuaternion& q) : x(q.getX()), y(q.getY()), z(q.getZ()), w(q.getW()) {}
	#endif
	friend T dot(const quatt &a, const quatt &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	friend quatt slerp(const quatt &x, const quatt &y, T a)
	{
		quatt z = y;
		T cosTheta = dot(x, y);
		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if (cosTheta < 0)
		{
			z = -y;
			cosTheta = -cosTheta;
		}
		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if (cosTheta > 1 - std::numeric_limits<T>::epsilon())
		{
			// Linear interpolation
			return quatt(
				lerp(x.x, z.x, a),
				lerp(x.y, z.y, a),
				lerp(x.z, z.z, a),
				lerp(x.w, z.w, a));
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (x * sin((1 - a) * angle) + z * sin(a * angle)) / sin(angle);
		}
	}
};
template <typename T>
vec3t<T>::vec3t(const quatt<T> &q)
{
	// https://en.wikipedia.org/wiki/Conversion_between_quats_and_Euler_angles
	vec3t<T> angles;
	// roll (x-axis rotation)
	T sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	T cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	x = atan2(sinr_cosp, cosr_cosp);
	// pitch (y-axis rotation)
	T sinp = sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	T cosp = sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	y = 2 * atan2(sinp, cosp) - PI / 2;
	// yaw (z-axis rotation)
	T siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	T cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	z = atan2(siny_cosp, cosy_cosp);
}
using quat = quatt<float>;


#endif