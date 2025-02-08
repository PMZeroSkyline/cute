#include "common.h"

template float radians<float>(float degrees);
template float degrees<float>(float degrees);
template float square<float>(float x);
template float mod<float>(float x, float y);
template float sign<float>(float val);
template float sgn<float>(float val);
template float lerp<float>(float a, float b, float w);
template float lerp<float>(float start, float end, float t, float r);

template double radians<double>(double degrees);
template double degrees<double>(double degrees);
template double square<double>(double x);
template double mod<double>(double x, double y);
template double sign<double>(double val);
template double sgn<double>(double val);
template double lerp<double>(double a, double b, double w);
template double lerp<double>(double start, double end, double t, double r);

template void sincos<float>(float v, float& s, float& c);
template void sincos<double>(double v, double& s, double& c);
