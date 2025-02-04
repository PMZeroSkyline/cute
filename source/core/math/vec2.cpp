#include "vec2.h"

template struct vec2t<unsigned char>;
template struct vec2t<unsigned short>;
template struct vec2t<unsigned int>;
template struct vec2t<int>;
template struct vec2t<float>;
template struct vec2t<double>;

template struct std::hash<vec2t<unsigned char>>;
template struct std::hash<vec2t<unsigned short>>;
template struct std::hash<vec2t<unsigned int>>;
template struct std::hash<vec2t<int>>;
template struct std::hash<vec2t<float>>;
template struct std::hash<vec2t<double>>;