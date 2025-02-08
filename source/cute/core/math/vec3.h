#ifndef VEC3_H
#define VEC3_H

#include <functional> // hash
#include <sstream> // os
#include <cmath> // std::abs
#include <algorithm> // std::clamp

template <typename T>
struct vec4t;
template <typename T>
struct quatt;

template <typename T>
struct vec3t
{
	T x, y, z;
	vec3t() : x(0), y(0), z(0) {}
	vec3t(T i) : x(i), y(i), z(i) {}
	vec3t(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template <typename U>
	vec3t(const vec3t<U> &v) : x(v.x), y(v.y), z(v.z) {}
	vec3t(const vec4t<T> &v);
	vec3t(const quatt<T> &q);
	vec3t operator+(const vec3t &v) const
	{
		return vec3t(x + v.x, y + v.y, z + v.z);
	}
	vec3t &operator+=(const vec3t &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	vec3t operator-(const vec3t &v) const
	{
		return vec3t(x - v.x, y - v.y, z - v.z);
	}
	vec3t &operator-=(const vec3t &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	friend vec3t operator*(T i, const vec3t &v)
	{
		return vec3t(i * v.x, i * v.y, i * v.z);
	}
	vec3t operator*(const vec3t &v) const
	{
		return vec3t(x * v.x, y * v.y, z * v.z);
	}
	vec3t &operator*=(const vec3t &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	vec3t operator/(T v) const
	{
		return vec3t(x / v, y / v, z / v);
	}
	vec3t operator/(const vec3t &v) const
	{
		return vec3t(x / v.x, y / v.y, z / v.z);
	}
	vec3t &operator/=(const vec3t &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	vec3t operator%(T v) const
	{
		return vec3t(fmod(x, v), fmod(y, v), fmod(z, v));
	}
	vec3t &operator%=(T v)
	{
		x = fmod(x, v);
		y = fmod(y, v);
		z = fmod(z, v);
		return *this;
	}
	bool operator==(const vec3t &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z);
	}
	bool operator!=(const vec3t &v) const
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
	vec3t operator-() const
	{
		return vec3t(-((float)x), -((float)y), -((float)z));
	}
	friend std::ostream &operator<<(std::ostream& os, const vec3t& v)
	{
		for (int i = 0; i < 3; i++)
		{
			T value = v[i];
			if (std::abs((double)value) <= std::numeric_limits<T>::epsilon())
			{
				value = 0;
			}
			os << value << " ";
		}
		return os;
	}
	#ifdef INCLUDE_NLOHMANN_JSON_HPP_
	friend void to_json(json& j, const vec3t& v) 
	{
		j[0] = v.x;
		j[1] = v.y;
		j[2] = v.z;
	}
	friend void from_json(const json& j, vec3t& v) 
	{
		v = *(vec3t*)j.get<std::array<T, 3>>().data();
	}
	#endif
	#ifdef BT_VECTOR3_H
	btVector3 bullet() 
	{
		return btVector3(x, y, z);
	}
	vec3t(const btVector3& v) : x(v.getX()), y(v.getY()), z(v.getZ()) {}
	#endif
	friend T dot(const vec3t &a, const vec3t &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	friend T square(const vec3t &v)
	{
		return dot(v, v);
	}
	friend vec3t abs(const vec3t &v)
	{
		return vec3t(std::abs((float)v.x), std::abs((float)v.y), std::abs((float)v.z));
	}
	friend vec3t min(const vec3t &a, const vec3t &b)
	{
		return vec3t(
			std::min(a.x, b.x),
			std::min(a.y, b.y),
			std::min(a.z, b.z));
	}
	friend vec3t max(const vec3t &a, const vec3t &b)
	{
		return vec3t(
			std::max(a.x, b.x),
			std::max(a.y, b.y),
			std::max(a.z, b.z));
	}
	friend vec3t clamp(const vec3t &v, const float &_min, const float& _max)
	{
		return vec3t(
			std::clamp((float)v.x, (float)_min, (float)_max),
			std::clamp((float)v.y, (float)_min, (float)_max),
			std::clamp((float)v.z, (float)_min, (float)_max));
	}
	friend vec3t cross(const vec3t &x, const vec3t &y)
	{
		return vec3t(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y);
	}
	friend vec3t reflect(const vec3t &incident, const vec3t &normal)
	{
		return incident - 2.0f * dot(incident, normal) * normal;
	}
	friend T length(const vec3t &v)
	{
		return sqrt(square(v));
	}
	friend vec3t normalize(const vec3t &v)
	{
		return v / length(v);
	}
	friend T distance(const vec3t &a, const vec3t &b)
	{
		return length(b - a);
	}
	friend vec3t pow(const vec3t &v, float power)
	{
		return vec3t(
			std::pow(v.x, power),
			std::pow(v.y, power),
			std::pow(v.z, power));
	}
};
template <typename T>
struct std::hash<vec3t<T>>
{
	size_t operator()(const vec3t<T>& v) const
	{
		std::size_t hx = std::hash<T>{}(v.x);
		std::size_t hy = std::hash<T>{}(v.y);
		std::size_t hz = std::hash<T>{}(v.z);
		return hx ^ (hy << 1) ^ (hz << 2);
	}
};
using u8vec3 = vec3t<unsigned char>;
using u16vec3 = vec3t<unsigned short>;
using uvec3 = vec3t<unsigned int>;
using ivec3 = vec3t<int>;
using vec3 = vec3t<float>;
using dvec3 = vec3t<double>;

#endif