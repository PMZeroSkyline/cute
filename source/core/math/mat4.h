#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"
#include "mat3.h"

template <typename T>
struct mat4t
{
	vec4t<T> value[4];
	mat4t()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
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
	mat4t(const std::initializer_list<vec4t<T>> &l)
	{
		for (int i = 0; i < 4; i++)
		{
			row(i, *(l.begin() + i));
		}
	}
	mat4t(const mat3t<T> &m)
	{
		row(0, m.row(0));
		row(1, m.row(1));
		row(2, m.row(2));
		row(3, vec4t<T>(0.0, 0.0, 0.0, 1.0));
	}
	T* data()
	{
		return &value[0][0];
	}
	const T* data() const
	{
		return &value[0][0];
	}
	void col(int i, const vec4t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[0][i] = v[0];
		value[1][i] = v[1];
		value[2][i] = v[2];
		value[3][i] = v[3];
		#else
		value[i] = v;
		#endif
	}
	const vec4t<T> col(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return vec4t<T>(value[0][i], value[1][i], value[2][i], value[3][i]);
		#else
		return value[i];
		#endif
	}
	void row(int i, const vec4t<T>& v)
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		value[i] = v;
		#else
		value[0][i] = v[0];
		value[1][i] = v[1];
		value[2][i] = v[2];
		value[3][i] = v[3];
		#endif
	}
	const vec4t<T> row(int i) const
	{ 
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return value[i];
		#else
		return vec4t<T>(value[0][i], value[1][i], value[2][i], value[3][i]);
		#endif
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
	mat4t operator*(const mat4t &m) const
	{
		mat4t r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r(i, j) = dot(row(i), m.col(j));
			}
		}
		return r;
	}
	mat4t operator*(const T& s) const
	{
		mat4t r = (*this);
		for (int i = 0; i < 4; i++)
		{
			r.value[i] *= s;
		}
		return r;
	}
	vec4t<T> operator*(const vec4t<T> &v) const
	{
		vec4t<T> r;
		for (int i = 0; i < 4; i++)
		{
			r[i] = dot(row(i), v);
		}
		return r;
	}
	bool operator==(const mat4t &m) const
	{
		for (int i = 0; i < 4; i++)
		{
			if (value[i] != m.value[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const mat4t &m) const
	{
		return !(*this == m);
	}
	mat3t<T> minor(int r, int c) const
	{
		mat3t<T> m;
		int x = 0;
		int y = 0;
		for (int i = 0; i < 4; i++)
		{
			if (i == r)
			{
				continue;
			}
			for (int j = 0; j < 4; j++)
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
	mat4t<T> minors() const
	{
		mat4t<T> m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m(i, j) = (*this).minor(i, j).determinant();
			}
		}
		return m;
	}
	T determinant() const
	{
		mat4t<T> m = (*this);
		m.col(3, m.col(3) - m.col(0));
		return m.minor(0, 0).determinant();
	}
	static mat4t cofactors()
	{
		mat4t m =  {
			{1.0, -1.0, 1.0, -1.0},
			{-1.0, 1.0, -1.0, 1.0},
			{1.0, -1.0, 1.0, -1.0},
			{-1.0, 1.0, -1.0, 1.0}
		};
		return m;
	}
	mat4t<T> cofactor(mat4t<T> _minors) const
	{
		mat4t<T> c = mat4t::cofactors();
		for (int i = 0; i < 4; i++)
		{
			_minors.value[i] *= c.value[i];
		}
		return _minors;
	}
	friend mat4t transpose(const mat4t &m)
	{
		mat4t t;
		for (int i = 0; i < 4; i++)
		{
			t.row(i, m.col(i));
		}
		return t;
	}
	mat4t<T> adjugate(mat4t<T> _minors) const
	{
		return transpose(cofactor(_minors));
	}
	friend mat4t inverse(const mat4t &m)
	{
		// https://www.youtube.com/watch?v=nNOz6Ez8Fn4
		return m.adjugate(m.minors()) * 0.5;
	}
	mat4t col_order() const
	{
		#ifdef MATRIX_ROW_MAJOR_ORDER
		return transpose();
		#else
		return *this;
		#endif
	}
	friend std::ostream &operator<<(std::ostream &os, const mat4t &m)
	{
		for (int i = 0; i < 4; i++)
		{
			os << m.row(i) << "\n";
		}
		return os;
	}
	#ifdef INCLUDE_NLOHMANN_JSON_HPP_
	friend void to_json(json& j, const mat4t& m) 
	{
		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				j[i*4+k] = m(k, i);
			}
		}
	}
	friend void from_json(const json& j, mat4t& m) 
	{
		m = *(mat4t*)j["matrix"].get<std::array<T, 16>>().data();
		#ifdef MATRIX_ROW_MAJOR_ORDER
        m = transpose(m);
		#endif
	}
	#endif
	static mat4t orthographic(T left, T right, T bottom, T top, T near, T far)
	{
		// https://en.wikipedia.org/wiki/Orthographic_projection
		T l = left, r = right, t = top, b = bottom, n = near, f = far;
		mat4t result = {
			{2 / (r - l), 0, 0, -(r + l) / (r - l)},
			{0, 2 / (t - b), 0, -(t + b) / (t - b)},
			{0, 0, -2 / (f - n), -(f + n) / (f - n)},
			{0, 0, 0, 1}};
		return result;
	}
	static mat4t orthographic(T xmag, T ymag, T znear, T zfar)
	{
		// https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#introduction-general
		T r = xmag, t = ymag, n = znear, f = zfar;
		mat4t result = {
			{1 / r, 0, 0, 0},
			{0, 1 / t, 0, 0},
			{0, 0, 2 / (n - f), (f + n) / (n - f)},
			{0, 0, 0, 1}};
		return result;
	}
	static mat4t perspective(T yfov, T aspect, T znear, T zfar)
	{
		T a = aspect, y = yfov, n = znear, f = zfar;
		// https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#introduction-general
		mat4t result = {
			{T(1) / (a * tan(T(0.5) * y)), 0, 0, 0},
			{0, T(1) / (tan(T(0.5) * y)), 0, 0},
			{0, 0, (f + n) / (n - f), (2 * f * n) / (n - f)},
			{0, 0, -1, 0}};
		return result;
	}
	static mat4t translate(const vec3t<T> &position)
	{
		mat4t M =  {{1, 0, 0, position.x},
					{0, 1, 0, position.y},
					{0, 0, 1, position.z},
					{0, 0, 0, 1}};
		return M;
	}
	static mat4t oblique_clipping(mat4t matrix, const vec4t<T>& clipPlane)
	{
		// https://terathon.com/blog/oblique-clipping.html
		vec4t<T> q;
		q.x = (sgn(clipPlane.x) + matrix(0, 2)) / matrix(0, 0);
		q.y = (sgn(clipPlane.y) + matrix(1, 2)) / matrix(1, 1);
		q.z = -1;
		q.w = (1 + matrix(2, 2)) / matrix(2, 3);
		vec4t<T> c = clipPlane * (2 / dot(clipPlane, q));
		matrix(2, 0) = c.x;
		matrix(2, 1) = c.y;
		matrix(2, 2) = c.z + 1;
		matrix(2, 3) = c.w;
		return matrix;
	}
	static mat4t mirror(const vec4t<T>& mirrorPlane)
	{
		const vec3t<T> n(mirrorPlane);
		T d = mirrorPlane.w;
		return {
			{1 - 2*n.x*n.x, -2*n.x*n.y, -2*n.x*n.z, -2*n.x*d},
			{-2*n.y*n.x, 1 - 2*n.y*n.y, -2*n.y*n.z, -2*n.y*d},
			{-2*n.z*n.x, -2*n.z*n.y, 1 - 2*n.z*n.z, -2*n.z*d},
			{0, 0, 0, 1}
		};
	}
	static bool decompose(mat4t m, vec3t<T> &Translation, quatt<T> &Orientation, vec3t<T> &Scale)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m(i, j) /= m(3, 3);
			}
		}
		Translation = vec3t<T>(m.col(3));
		for (int i = 0; i < 3; i++)
		{
			Scale[i] = length(m.col(i));
		}
		mat3t<T> m3 = mat3t<T>(m);
		vec3t<T> Pdum3 = cross(vec3t<T>(m3.col(1)), vec3t<T>(m3.col(2)));
		if (dot(vec3t<T>(m3.col(0)), Pdum3) < 0)
		{
			for (int i = 0; i < 3; i++)
			{
				Scale[i] *= -1;
				m3.value[i] *= -1;
			}
		}
		m3.col(0, normalize(m3.col(0)));
		m3.col(1, normalize(m3.col(1)));
		m3.col(2, normalize(m3.col(2)));
		int i, j, k = 0;
		T root, trace = m3(0, 0) + m3(1, 1) + m3(2, 2);
		if (trace > 0)
		{
			root = sqrt(trace + 1);
			Orientation.w = .5 * root;
			root = .5 / root;
			Orientation.x = root * (m3(2, 1) - m3(1, 2));
			Orientation.y = root * (m3(0, 2) - m3(2, 0));
			Orientation.z = root * (m3(1, 0) - m3(0, 1));
		} // End if > 0
		else
		{
			static int Next[3] = {1, 2, 0};
			i = 0;
			if (m3(1, 1) > m3(0, 0))
				i = 1;
			if (m3(2, 2) > m3(i, i))
				i = 2;
			j = Next[i];
			k = Next[j];
			root = sqrt(m3(i, i) - m3(j, j) - m3(k, k) + 1);
			Orientation[i] = .5 * root;
			root = .5 / root;
			Orientation[j] = root * (m3(j, i) + m3(i, j));
			Orientation[k] = root * (m3(k, i) + m3(i, k));
			Orientation.w = root * (m3(k, j) - m3(j, k));
		} // End if <= 0
		return true;
	}
};
template <typename T>
mat3t<T>::mat3t(const mat4t<T> &m)
{
	value[0] = vec3t<T>(m.value[0]);
	value[1] = vec3t<T>(m.value[1]);
	value[2] = vec3t<T>(m.value[2]);
}
using mat4 = mat4t<float>;


#endif