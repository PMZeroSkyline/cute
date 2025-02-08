#include "hdr_lighting.h"

std::shared_ptr<TextureCube> hdr_cube(const std::string& hdr_path, int size)
{
    std::shared_ptr<Texture2D> hdr_texture = Texture2D::get(hdr_path, true, TextureSampler::make_linear_clamp_to_edge(), false);
    std::shared_ptr<TextureCube> dst_texture = std::make_shared<TextureCube>(GL_FLOAT, size, 3, 1, "", TextureSampler::make_linear_mipmap_clamp_to_edge(), true);
    std::shared_ptr<Program> program = Program::get("assets/shader/environment.vert,UNIFORM_VP", "assets/shader/equirectangular.frag");
    std::shared_ptr<Material> capture_material = std::make_shared<Material>();
    capture_material->floats[HashedString("iIntensity")] = 1.f;
    capture_material->textures[HashedString("iEnvironmentTexture")] = hdr_texture;
    std::shared_ptr<MeshPrimitive> primitive = MeshPrimitive::make_cube();
    PerspectiveCamera camera(1.f, radians(90.f), 0.1f, 10.f);
    mat4 iP = camera.get_projection();
    iP(1, 1) *= -1.f; // cubemap need in flipped space save
    std::array<quat, 6> orientations = TextureCube::orientations();
    ViewportStash stash;
    glViewport(0, 0, size, size);
    std::shared_ptr<Framebuffer> capture_framebuffer = std::make_shared<Framebuffer>();
    capture_framebuffer->Bind();
    for (int i = 0; i < 6; i++)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, dst_texture->id, 0);
        gl_check_framebuffer_complete();
        capture_material->submit(program.get());
        program->uniform_matrix4f("iVP", iP * inverse(mat4(orientations[i])));
        program->uniform_matrix4f("iM", mat4());
        primitive->vertex_array->bind();
        glDrawElements(GL_TRIANGLES, primitive->indices->size(), GL_UNSIGNED_INT, 0);
    }
    dst_texture->bind();
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    return dst_texture;
}
