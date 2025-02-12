#include "render_engine.h"

RenderEngine::RenderEngine() {}
void RenderEngine::render() 
{
    for (auto& pass : passes)
    {
        pass->render();
    }
}