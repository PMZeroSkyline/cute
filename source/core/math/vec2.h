#ifndef VEC2_H
#define VEC2_H

#include <functional> // hash
#include <sstream> // os
#include <cmath> // std::abs

template <typename T>
struct vec2t
{
	T x, y;
	vec2t() : x(0), y(0) {}
	vec2t(T i) : x(i), y(i) {}
	vec2t(T _x, T _y) : x(_x), y(_y) {}
	template <typename U>
	vec2t(const vec2t<U> &v) : x(v.x), y(v.y) {}
	vec2t operator+(const vec2t &v) const
	{
		return vec2t(x + v.x, y + v.y);
	}
	vec2t &operator+=(const vec2t &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2t operator-(const vec2t &v) const
	{
		return vec2t(x - v.x, y - v.y);
	}
	vec2t &operator-=(const vec2t &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vec2t operator*(const vec2t &v) const
	{
		return vec2t(x * v.x, y * v.y);
	}
	vec2t &operator*=(const vec2t &v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	vec2t operator/(const vec2t &v) const
	{
		return vec2t(x / v.x, y / v.y);
	}
	vec2t &operator/=(const vec2t &v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}
	bool operator==(const vec2t &v) const
	{
		return (x == v.x) && (y == v.y);
	}
	bool operator!=(const vec2t &v) const
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
	vec2t operator-() const
	{
		return vec2t(-((float)x), -((float)y));
	}
    friend vec2t operator*(T i, const vec2t &v)
	{
		return vec2t(i * v.x, i * v.y);
	}
	friend T length(const vec2t &v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}
	friend vec2t normalize(const vec2t &v)
	{
		return v / length(v);
	}
	friend std::ostream &operator<<(std::ostream &os, const vec2t &v)
	{
		for (int i = 0; i < 2; i++)
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
	friend void to_json(json& j, const vec2t& v) 
	{
		j[0] = v.x;
		j[1] = v.y;
	}
	friend void from_json(const json& j, vec2t& v) 
	{
		v = *(vec2t*)j.get<std::array<T, 2>>().data();
	}
	#endif
	friend T dot(const vec2t &a, const vec2t &b)
	{
		return a.x * b.x + a.y * b.y;
	}
};
template <typename T>
struct std::hash<vec2t<T>>
{
	size_t operator()(const vec2t<T>& v) const
	{
		std::size_t hx = std::hash<T>{}(v.x);
		std::size_t hy = std::hash<T>{}(v.y);
		return hx ^ (hy << 1);
	}
};
using u8vec2 = vec2t<unsigned char>;
using u16vec2 = vec2t<unsigned short>;
using uvec2 = vec2t<unsigned int>;
using ivec2 = vec2t<int>;
using vec2 = vec2t<float>;
using dvec2 = vec2t<double>;

#endif