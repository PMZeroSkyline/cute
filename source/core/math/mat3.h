#ifndef MAT3_H
#define MAT3_H

#include "quat.h"
#include "mat2.h"

template <typename T>
struct mat4t;

template <typename T>
struct mat3t
{
	// TODO: Support other major order, or swith to Column-Major Order
	vec3t<T> value[3];
	mat3t()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == j)
				{
					(*this)(i, j) = 1;
				}
				else
				{
					(*this)(i, j) = 0;
				}
			}
		}
	}
	mat3t(const vec3t<T> &row0, const vec3t<T> &row1, const vec3t<T> &row2)
	{
		row(0, row0);
		row(1, row1);
		row(2, row2);
	}
	mat3t(const vec3t<T> &diagonal)
	{
		(*this) = {
			{diagonal.x, 0.0, 0.0},
			{0.0, diagonal.y, 0.0},
			{0.0, 0.0, diagonal.z}
		};
	}
	explicit mat3t(const T& diagonal)
	{
		(*this) = {
			{diagonal, 0.0, 0.0},
			{0.0, diagonal, 0.0},
			{0.0, 0.0, diagonal}
		};
	}
	mat3t(const mat4t<T> &m);
	mat3t(const quatt<T> &q)
	{
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		T qxx = q.x * q.x;
		T qyy = q.y * q.y;
		T qzz = q.z * q.z;
		T qxy = q.x * q.y;
		T qxz = q.x * q.z;
		T qyz = q.y * q.z;
		T qwx = q.w * q.x;
		T qwy = q.w * q.y;
		T qwz = q.w * q.z;
		*this = {
			{1 - 2 * (qyy + qzz), 2 * (qxy - qwz), 2 * (qwy + qxz)},
			{2 * (qxy + qwz), 1 - 2 * (qxx + qzz), 2 * (qyz - qwx)},
			{2 * (qxz - qwy), 2 * (qwx + qyz), 1 - 2 * (qxx + qyy)}};
	}
	T* data()
	{
		return &value[0][0];
	}
	const T* data() const
	{
		return &value[0][0];
	}
	void col(int i, const vec3t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[0][i] = v[0];
		value[1][i] = v[1];
		value[2][i] = v[2];
		#else
		value[i] = v;
		#endif
	}
	const vec3t<T> col(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return vec3t<T>(value[0][i], value[1][i], value[2][i]);
		#else
		return value[i];
		#endif
	}
	void row(int i, const vec3t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[i] = v;
		#else
		value[0][i] = v[0];
		value[1][i] = v[1];
		value[2][i] = v[2];
		#endif
	}
	const vec3t<T> row(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return value[i];
		#else
		return vec3t<T>(value[0][i], value[1][i], value[2][i]);
		#endif
	}
	mat2t<T> minor(int r, int c) const
	{
		mat2t<T> m;
		int x = 0;
		int y = 0;
		for (int i = 0; i < 3; i++)
		{
			if (i == r)
			{
				continue;
			}
			for (int j = 0; j < 3; j++)
			{
				if (j == c)
				{
					continue;
				}
				m(x, y) = (*this)(i, j);
				y++;
			}
			x++;
			y = 0;
		}
		return m;
	}
	mat3t<T> minors() const
	{
		mat3t<T> m;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m(i, j) = (*this).minor(i, j).determinant();
			}
		}
		return m;
	}
	T& operator()(int r, int c)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return value[r][c];
		#else
		return value[c][r];
		#endif
	}
	const T& operator()(int r, int c) const 
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return value[r][c];
		#else
		return value[c][r];
		#endif
	}
	mat3t operator*(const mat3t &m) const
	{
		mat3t r;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				r(i, j) = dot(row(i), m.col(j));
			}
		}
		return r;
	}
	vec3t<T> operator*(const vec3t<T> &v) const
	{
		vec3t<T> r;
		for (int i = 0; i < 3; i++)
		{
			r[i] = dot(row(i), v);
		}
		return r;
	}
	bool operator==(const mat3t &m) const
	{
		for (int i = 0; i < 3; i++)
		{
			if (value[i] != m.value[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const mat3t &m) const
	{
		return !(*this == m);
	}	
	friend std::ostream &operator<<(std::ostream &os, const mat3t &m)
	{
		for (int i = 0; i < 3; i++)
		{
			os << m.row(i) << "\n";
		}
		return os;
	}
	friend mat3t transpose(const mat3t &m)
	{
		mat3t r;
		for (int i = 0; i < 3; i++)
		{
			r.row(i, m.col(i));
		}
		return r;
	}
	static mat3t scale(const vec3t<T> &scale)
	{
		// https://en.wikipedia.org/wiki/Scaling_(geometry)
		mat3t S = {{scale.x, 0, 0},
					{0, scale.y, 0},
					{0, 0, scale.z}};
		return S;
	}
	static mat3t cofactors()
	{
		mat3t m =  {
			{1.0, -1.0, 1.0},
			{-1.0, 1.0, -1.0},
			{1.0, -1.0, 1.0}
		};
		return m;
	}
	mat3t<T> cofactor(mat3t<T> _minors) const
	{
		mat3t<T> c = mat3t::cofactors();
		for (int i = 0; i < 3; i++)
		{
			_minors.value[i] *= c.value[i];
		}
		return _minors;
	}
	mat3t<T> adjugate(mat3t<T> _minors) const
	{
		return transpose(cofactor(_minors));
	}
	T determinant() const
	{
		const mat3t<T> m = (*this);
		return m(0, 0) * m.minor(0, 0).determinant() - m(0, 1) * m.minor(0, 1).determinant() + m(0, 2) * m.minor(0, 2).determinant();
	}
	T determinant(const mat3t<T>& _minors) const
	{
		const mat3t<T> m = (*this);
		return m(0, 0) * _minors(0, 0) - m(0, 1) * _minors(0, 1) + m(0, 2) * _minors(0, 2);
	}
	friend mat3t inverse(const mat3t &m)
	{
		// https://www.youtube.com/watch?v=kWorj5BBy9k&list=PLybg94GvOJ9FoGQeUMFZ4SWZsr30jlUYK&index=144
		mat3t<T> mi = m.minors();
		mat3t<T> ad = m.adjugate(mi);
		T det = m.determinant(mi);
		for (int i = 0; i < 3; i++)
		{
			ad.value[i] /= det;
		}
		return ad;
	}
};
template <typename T>
quatt<T>::quatt(const mat3t<T> &m)
{
	// https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
	// https://www.youtube.com/watch?v=8FfFH9PKHiY
	float trace = m(0, 0) + m(1, 1) + m(2, 2);
	if (trace > 0)
	{
		float s = 0.5f / sqrtf(trace + 1.0f);
		w = 0.25f / s;
		x = (m(2, 1) - m(1, 2)) * s;
		y = (m(0, 2) - m(2, 0)) * s;
		z = (m(1, 0) - m(0, 1)) * s;
	}
	else
	{
		if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2))
		{
			float s = 2.0f * sqrtf(1.0f + m(0, 0) - m(1, 1) - m(2, 2));
			w = (m(2, 1) - m(1, 2)) / s;
			x = 0.25f * s;
			y = (m(0, 1) + m(1, 0)) / s;
			z = (m(0, 2) + m(2, 0)) / s;
		}
		else if (m(1, 1) > m(2, 2))
		{
			float s = 2.0f * sqrtf(1.0f + m(1, 1) - m(0, 0) - m(2, 2));
			w = (m(0, 2) - m(2, 0)) / s;
			x = (m(0, 1) + m(1, 0)) / s;
			y = 0.25f * s;
			z = (m(1, 2) + m(2, 1)) / s;
		}
		else
		{
			float s = 2.0f * sqrtf(1.0f + m(2, 2) - m(0, 0) - m(1, 1));
			w = (m(1, 0) - m(0, 1)) / s;
			x = (m(0, 2) + m(2, 0)) / s;
			y = (m(1, 2) + m(2, 1)) / s;
			z = 0.25f * s;
		}
	}
}
using mat3 = mat3t<float>;


#endif