#include "vec3.h"

template struct std::hash<vec3t<unsigned char>>;
template struct std::hash<vec3t<unsigned short>>;
template struct std::hash<vec3t<unsigned int>>;
template struct std::hash<vec3t<int>>;
template struct std::hash<vec3t<float>>;
template struct std::hash<vec3t<double>>;