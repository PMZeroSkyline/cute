#ifndef VEC4_H
#define VEC4_H

#include "vec3.h"

template <typename T>
struct vec4t
{
	T x, y, z, w;
	vec4t() : x(0), y(0), z(0), w(0) {}
	vec4t(T i) : x(i), y(i), z(i), w(i) {}
	vec4t(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	vec4t(const vec3t<T> &v) : x(v.x), y(v.y), z(v.z), w(0) {}
	vec4t(const vec3t<T> &v, T _w) : x(v.x), y(v.y), z(v.z), w(_w) {}
	template <typename U>
	vec4t(const vec4t<U> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	vec4t operator+(const vec4t &v) const
	{
		return vec4t(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	vec4t &operator+=(const vec4t &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	vec4t operator-(const vec4t &v) const
	{
		return vec4t(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	vec4t &operator-=(const vec4t &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	vec4t operator*(const vec4t &v) const
	{
		return vec4t(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	friend vec4t operator*(T i, const vec4t &v)
	{
		return vec4t(i * v.x, i * v.y, i * v.z, i * v.w);
	}
	vec4t &operator*=(const vec4t &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}
	vec4t operator/(const vec4t &v) const
	{
		return vec4t(x / v.x, y / v.y, z / v.z, w / v.w);
	}
	vec4t &operator/=(const vec4t &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
	vec4t operator-() const
	{
		return vec4t(-((float)x), -((float)y), -((float)z), -((float)w));
	}
	bool operator==(const vec4t &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	}
	bool operator!=(const vec4t &v) const
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
	friend T length(const vec4t &v)
	{
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}
	friend vec4t normalize(const vec4t &v)
	{
		return v / length(v);
	}
	friend T dot(const vec4t &a, const vec4t &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	friend vec4t clamp(const vec4t &v, const float &_min, const float& _max)
	{
		return vec4t(
			std::clamp((float)v.x, (float)_min, (float)_max),
			std::clamp((float)v.y, (float)_min, (float)_max),
			std::clamp((float)v.z, (float)_min, (float)_max),
			std::clamp((float)v.w, (float)_min, (float)_max));
	}
	friend std::ostream &operator<<(std::ostream &os, const vec4t &v)
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
	friend void to_json(json& j, const vec4t& v) 
	{
		j[0] = v.x;
		j[1] = v.y;
		j[2] = v.z;
		j[3] = v.w;
	}
	friend void from_json(const json& j, vec4t& v) 
	{
		v = *(vec4t*)j.get<std::array<T, 4>>().data();
	}
	#endif
	friend vec4t abs(const vec4t &v)
	{
		return vec4t(std::abs((float)v.x), std::abs((float)v.y), std::abs((float)v.z), std::abs((float)v.w));
	}
	friend vec4t min(const vec4t &a, const vec4t &b)
	{
		return vec4t(
			std::min(a.x, b.x),
			std::min(a.y, b.y),
			std::min(a.z, b.z),
			std::min(a.w, b.w));
	}
	friend vec4t max(const vec4t &a, const vec4t &b)
	{
		return vec4t(
			std::max(a.x, b.x),
			std::max(a.y, b.y),
			std::max(a.z, b.z),
			std::max(a.w, b.w));
	}
};
template <typename T>
struct std::hash<vec4t<T>>
{
	size_t operator()(const vec4t<T>& v) const
	{
		std::size_t hx = std::hash<T>{}(v.x);
		std::size_t hy = std::hash<T>{}(v.y);
		std::size_t hz = std::hash<T>{}(v.z);
		std::size_t hw = std::hash<T>{}(v.w);
		return hx ^ (hy << 1) ^ (hz << 2) ^ (hw << 3);
	}
};
template <typename T>
vec3t<T>::vec3t(const vec4t<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
using u8vec4 = vec4t<unsigned char>;
using u16vec4 = vec4t<unsigned short>;
using uvec4 = vec4t<unsigned int>;
using ivec4 = vec4t<int>;
using vec4 = vec4t<float>;

#endif