#include "viewport_guard.h"

ViewportGuard::ViewportGuard() 
{
    glGetIntegerv(GL_VIEWPORT, viewport);
}
ViewportGuard::~ViewportGuard() 
{
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}