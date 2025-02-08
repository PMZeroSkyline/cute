#include "vec4.h"

template struct std::hash<vec4t<unsigned char>>;
template struct std::hash<vec4t<unsigned short>>;
template struct std::hash<vec4t<unsigned int>>;
template struct std::hash<vec4t<int>>;
template struct std::hash<vec4t<float>>;
template struct std::hash<vec4t<double>>;
