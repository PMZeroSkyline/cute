#ifndef RENDER_PASS_H
#define RENDER_PASS_H

struct RenderPass
{
    int priority = 0;
    virtual void render() = 0;
};

#endif