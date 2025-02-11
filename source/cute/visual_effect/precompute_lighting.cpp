#include "precompute_lighting.h"
#include "platform/graphics_wrapper/framebuffer.h"
#include "renderer/perspective_camera.h"
#include "renderer/viewport_guard.h"
#include "resource/mesh_primitive.h"

std::shared_ptr<TextureCube> render_ibl_diffuse(const std::shared_ptr<TextureCube>& hdr_cube, int size)
{
    std::shared_ptr<TextureCube> dst_cube = std::make_shared<TextureCube>(GL_FLOAT, size, 3, 1, "", TextureSampler::make_linear_clamp_to_edge(), false);
    std::shared_ptr<Material> material = std::make_shared<Material>();
    std::shared_ptr<Program> program = Program::get("assets/shader/precompute_lighting/vs_cube.glsl", "assets/shader/precompute_lighting/fs_ibl_diffuse.glsl");
    material->textures[HashedString("iEnvironmentTexture")] = hdr_cube;
    std::shared_ptr<MeshPrimitive> primitive = MeshPrimitive::make_cube();
    PerspectiveCamera camera(1.f, radians(90.f), 0.1f, 10.f);
    mat4 iP = camera.get_projection();
    iP(1, 1) *= -1.f; // cubemap need in flipped space save
    std::array<quat, 6> orientations = TextureCube::orientations();
    ViewportGuard guard;
    glViewport(0, 0, size, size);
    std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>();
    framebuffer->bind();
    for (int i = 0; i < 6; i++)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, dst_cube->id, 0);
        gl_check_framebuffer_complete();
        material->submit(program.get());
        program->uniform_matrix4f(HashedString("iMVP"), iP * inverse(mat4(orientations[i])));
        primitive->vertex_array->bind();
        glDrawElements(GL_TRIANGLES, primitive->indices->size(), GL_UNSIGNED_INT, 0);
        dst_cube->mipmaps[0][i]->alloc();
        glReadPixels(0, 0, size, size, GL_RGB, GL_FLOAT, dst_cube->mipmaps[0][i]->data);
    }
    return dst_cube;
}
std::shared_ptr<TextureCube> render_ibl_specular(const std::shared_ptr<TextureCube>& hdr_cube, int size)
{
    const int mip_count = 5;
    std::shared_ptr<TextureCube> dst_cube = std::make_shared<TextureCube>(GL_FLOAT, size, 3, mip_count, "", TextureSampler::make_linear_mipmap_clamp_to_edge(), true);
    std::shared_ptr<Material> material = std::make_shared<Material>();
    std::shared_ptr<Program> program = Program::get("assets/shader/precompute_lighting/vs_cube.glsl", "assets/shader/precompute_lighting/fs_ibl_specular.glsl");
    material->textures[HashedString("iEnvironmentTexture")] = hdr_cube;
    std::shared_ptr<MeshPrimitive> primitive = MeshPrimitive::make_cube();
    PerspectiveCamera camera(1.f, radians(90.f), 0.1f, 10.f);
    mat4 iP = camera.get_projection();
    iP(1, 1) *= -1.f; // cubemap need in flipped space save
    std::array<quat, 6> orientations = TextureCube::orientations();
    std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>();
    framebuffer->bind();
    ViewportGuard guard;
    for (int mip = 0; mip < mip_count; mip++)
    {
        int mip_size  = size * std::pow(0.5, mip);
        material->floats[HashedString("iRoughness")] = (float)mip / (float)(mip_count - 1);
        glViewport(0, 0, mip_size, mip_size);
        for (int i = 0; i < 6; i++)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, dst_cube->id, mip);
            gl_check_framebuffer_complete();
            material->submit(program.get());
            program->uniform_matrix4f(HashedString("iMVP"), iP * inverse(mat4(orientations[i])));
            primitive->vertex_array->bind();
            glDrawElements(GL_TRIANGLES, primitive->indices->size(), GL_UNSIGNED_INT, 0);
        }
    }
    return dst_cube;
}
std::shared_ptr<Texture2D> render_brdf_lut(int size)
{
    std::shared_ptr<Texture2D> dst_2d = std::make_shared<Texture2D>(GL_FLOAT, size, size, 3, 1, "", TextureSampler::make_linear_clamp_to_edge(), false);
    std::shared_ptr<MeshPrimitive> primitive = MeshPrimitive::make_plane();
    std::shared_ptr<Material> material = std::make_shared<Material>();
    std::shared_ptr<Program> program = Program::get("assets/shader/precompute_lighting/vs_fullscreen.glsl", "assets/shader/precompute_lighting/fs_brdf_lut.glsl");
    ViewportGuard guard;
    glViewport(0, 0, size, size);
    std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>();
    framebuffer->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dst_2d->id, 0);
    gl_check_framebuffer_complete();
    material->submit(program.get());
    primitive->vertex_array->bind();
    glDrawElements(GL_TRIANGLES, primitive->indices->size(), GL_UNSIGNED_INT, 0);
    return dst_2d;
}
