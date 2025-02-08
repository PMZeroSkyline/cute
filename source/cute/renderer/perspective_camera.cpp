#include "perspective_camera.h"

PerspectiveCamera::PerspectiveCamera(float _aspectRatio, float _yfov, float _znear, float _zfar) : aspect_ratio(_aspectRatio), yfov(_yfov), Camera(_znear, _zfar) {}
PerspectiveCamera::PerspectiveCamera(const json& j) : Camera(j)
{
    json pers = j["perspective"];
    if (pers.contains("aspectRatio"))
    {
        aspect_ratio = pers["aspectRatio"];
    }
    yfov = pers["yfov"];
    zfar = pers["zfar"];
    znear = pers["znear"];
}
mat4 PerspectiveCamera::get_projection() const
{
    return mat4::perspective(yfov, aspect_ratio, znear, zfar);
}