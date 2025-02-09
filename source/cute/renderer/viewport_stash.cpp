#include "viewport_stash.h"

ViewportStash::ViewportStash() 
{
    glGetIntegerv(GL_VIEWPORT, viewport);
}
ViewportStash::~ViewportStash() 
{
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}