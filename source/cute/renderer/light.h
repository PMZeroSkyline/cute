#ifndef LIGHT_H
#define LIGHT_H

#include "core/parser/json.h"
struct Light
{
    std::string name;
    float intensity = 1.f;
    Light() = default;
    Light(const json& j);
    virtual ~Light();
};

#endif