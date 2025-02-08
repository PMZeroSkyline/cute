#include "camera.h"

Camera::Camera(float _znear, float _far) : znear(_znear), zfar(_far) {}

Camera::Camera(const json& j)
{
    if (j.contains("name"))
    {
        name = j["name"];
    }
}