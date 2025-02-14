#include "prt_lighting_pass.h"
#include "device/app.h"
#include "resource/material.h"
#include "renderer/viewport_guard.h"
#include "render_world.h"

void PRTLightingPass::on_resize()
{
    framebuffer->bind();
    color_attchment = std::make_shared<Texture2D>(GL_FLOAT, render_size.x, render_size.y, 3, 1, "", TextureSampler::make_nearest_clamp(), false);
    depth_attchment = std::make_shared<Texture2D>(GL_FLOAT, render_size.x, render_size.y, 1, 1, "", TextureSampler::make_nearest_clamp(), false, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT);
    Material().submit_state();
    gl_check_framebuffer_complete();
}
void PRTLightingPass::render()
{
    if (render_size != App::instance->window->render_size)
    {
        render_size = App::instance->window->render_size;
        on_resize();
    }
    
    ViewportGuard guard;
    glViewport(0, 0, render_size.x, render_size.y);
    framebuffer->bind();
    for (auto& render_object : RenderWorld::instance->render_objects)
    {
        draw_render_object(render_object);
    }
}
void PRTLightingPass::draw_render_object(const RenderObject& render_object)
{
    for (auto& primtive : render_object.mesh->primitives)
    {
        Material* material = primtive->material.get();
        if (!material) continue;
        Program* program;
        if (render_object.mesh_gpu_instancing)
        {
            static HashedString require_defines("INSTANCING");
            program = material->require(require_defines);
        }
        else
        {
            program = material->programs[HashedString()].get();
        }
        material->submit(program);
        program->uniform_matrix4f("iM", render_object.node->world_matrix);
        primtive->vertex_array->bind();
        if (render_object.mesh_gpu_instancing)
        {
            glDrawElementsInstanced(GL_TRIANGLES, primtive->indices->size(), GL_UNSIGNED_INT, 0, render_object.mesh_gpu_instancing->TRANSLATION.size());
        }
        else
        {
            glDrawElements(GL_TRIANGLES, primtive->indices->size(), GL_UNSIGNED_INT, 0);
        }
    }
}