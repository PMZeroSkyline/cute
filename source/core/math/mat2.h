#ifndef MAT2_H
#define MAT2_H

#include "vec2.h"

template <typename T>
struct mat2t
{
	vec2t<T> value[2];
	mat2t()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
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
	mat2t(const vec2t<T> &row0, const vec2t<T> &row1)
	{
		row(0, row0);
		row(1, row1);
	}
	T* data()
	{
		return &value[0][0];
	}
	const T* data() const
	{
		return &value[0][0];
	}
	void col(int i, const vec2t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[0][i] = v[0];
		value[1][i] = v[1];
		#else
		value[i] = v;
		#endif
	}
	const vec2t<T> col(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return vec2t<T>(value[0][i], value[1][i]);
		#else
		return value[i];
		#endif
	}
	void row(int i, const vec2t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[i] = v;
		#else
		value[0][i] = v[0];
		value[1][i] = v[1];
		#endif
	}
	const vec2t<T> row(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return value[i];
		#else
		return vec2t<T>(value[0][i], value[1][i]);
		#endif
	}
	T determinant() const
	{
		const mat2t m = (*this);
		return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
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
	mat2t operator*(const mat2t &m) const
	{
		mat2t r;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				r(i, j) = dot(row(i), m.col(j));
			}
		}
		return r;
	}
	vec2t<T> operator*(const vec2t<T> &v) const
	{
		vec2t<T> r;
		for (int i = 0; i < 2; i++)
		{
			r[i] = dot(row(i), v);
		}
		return r;
	}
	mat2t operator*(const T& s) const
	{
		mat2t r = (*this);
		r.value[0] *= s;
		r.value[1] *= s;
		return r;
	}
	mat2t operator/(const T& s) const
	{
		mat2t r = (*this);
		r.value[0] /= s;
		r.value[1] /= s;
		return r;
	}
	mat2t operator*=(const T& s)
	{
		value[0] *= s;
		value[1] *= s;
		return (*this);
	}
	mat2t operator/(const T& s)
	{
		value[0] /= s;
		value[1] /= s;
		return (*this);
	}
	bool operator==(const mat2t &m) const
	{
		for (int i = 0; i < 2; i++)
		{
			if (value[i] != m.value[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const mat2t &m) const
	{
		return !(*this == m);
	}
	mat2t transpose() const
	{
		mat2t m;
		for (int i = 0; i < 2; i++)
		{
			m.row(i, col(i));
		}
		return m;
	}
	friend std::ostream &operator<<(std::ostream &os, const mat2t &m)
	{
		for (int i = 0; i < 2; i++)
		{
			os << m.row(i) << "\n";
		}
		return os;
	}
	friend mat2t inverse(const mat2t &m)
	{
		mat2t inv = {
			{m(1, 1), -m(0, 1)},
			{-m(1, 0), m(0, 0)}
		};
		return inv / m.determinant();
	}
};
using mat2 = mat2t<float>;


#endif