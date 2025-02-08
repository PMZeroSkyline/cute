#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include <math.h>
// ----
#ifndef PI
#define PI 3.14159265358979323846264338327950288
#endif

// ----
template <typename T>
T radians(T degrees)
{
	return ((degrees * PI) / 180.0);
}
template <typename T>
T degrees(T radians)
{
	return ((radians * 180.0) / PI);
}
template <typename T>
T square(T x) {
    return x * x;
}
template <typename T>
T mod(T x, T y)
{
	T o = (T)fmod((float)x, (float)y);
	o = o < 0 ? o + y : o;
	return o;
}
template <typename T>
void sincos(T v, T &s, T &c)
{
	s = sin(v);
	c = cos(v);
}
template <typename T>
T sign(T val) {
	return (val > 0) - (val < 0);
}
template <typename T>
T sgn(T val) {
	return (val > 0) - (val < 0);
}
template <typename T, typename U>
T lerp(T a, T b, U w)
{
	return a + (b - a) * w;
}
template <typename T>
T lerp(T start, T end, T t, T r)
{
	T a = mod(start, r);
	T b = mod(end, r);
	T cw = a < b ? b - a : r - a + b;
	T ccw = a < b ? a + r - b : a - b;
	return cw < ccw ? mod(a + cw * t, r) : mod(a - ccw * t, r);
}

#endif