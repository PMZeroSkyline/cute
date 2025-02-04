#include "other.h"
#include <iostream>
void Foo()
{
    std::cout << is_pow_of_two(1024) << std::endl;
    std::cout << vec2(1.5f) << std::endl;
    std::cout << vec3(1.6f) << std::endl;
    std::cout << vec4(1.7f) << std::endl;
    quat q;
    mat3 m(q);
    std::cout << m(1, 1) << std::endl;
}