#include "orthographic_camera.h"

OrthographicCamera::OrthographicCamera(const json& j) : Camera(j)
{
    json orth = j["orthographic"];
    xmag = orth["xmag"];
    ymag = orth["ymag"];
    zfar = orth["zfar"];
    znear = orth["znear"];
}
mat4 OrthographicCamera::get_projection() const
{
    return mat4::orthographic(xmag, ymag, znear, zfar);
}