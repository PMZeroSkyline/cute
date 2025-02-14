#ifndef PRT_LIGHTING_PASS_H
#define PRT_LIGHTING_PASS_H
#include <memory>
#include "renderer/render_pass.h"
#include "renderer/texture_2d.h"
#include "platform/graphics_wrapper/framebuffer.h"
#include "core/math/vec2.h"
struct PRTLightingPass : RenderPass
{
    std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>();
    std::shared_ptr<Texture2D> color_attchment;
    std::shared_ptr<Texture2D> depth_attchment;
    ivec2 render_size;
    void render() override;
    void on_resize();
};
#endif