#include "equirectangular_mapping.h"
#include "platform/graphics_wrapper/framebuffer.h"
#include "renderer/perspective_camera.h"
#include "renderer/viewport_guard.h"
#include "resource/mesh_primitive.h"

std::shared_ptr<TextureCube> render_equirectangular_to_cube(const std::shared_ptr<Texture2D>& hdr_2d, int size)
{
    std::shared_ptr<TextureCube> dst_cube = std::make_shared<TextureCube>(GL_FLOAT, size, 3, 1, "", TextureSampler::make_linear_mipmap_clamp_to_edge(), true);
    std::shared_ptr<Material> material = std::make_shared<Material>();
    std::shared_ptr<Program> program = Program::get("source/cute/visual_effect/shader/environment_mapping/vs_cube.glsl", "source/cute/visual_effect/shader/environment_mapping/fs_cube.glsl");
    material->floats[HashedString("iIntensity")] = 1.f;
    material->textures[HashedString("iEnvironmentTexture")] = hdr_2d;
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
    }
    dst_cube->bind();
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    return dst_cube;
}
