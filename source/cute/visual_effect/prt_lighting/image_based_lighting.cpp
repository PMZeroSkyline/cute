#include "image_based_lighting.h"
#include "visual_effect/environment_mapping/precompute_ibl.h"
#include "visual_effect/environment_mapping/equirectangular_mapping.h"
#include "spherical_harmonics.h"

std::shared_ptr<ImageBasedLight> make_image_based_light(const std::string& hdr_path, float intensity)
{
    std::shared_ptr<Texture2D> hdr_2d = Texture2D::get(hdr_path, true, TextureSampler::make_linear_clamp_to_edge(), false);
    std::shared_ptr<TextureCube> hdr_cube = render_equirectangular_to_cube(hdr_2d, hdr_2d->mipmaps[0]->x / 2);
    std::shared_ptr<TextureCube> diffuse_cube = precompute_ibl_diffuse(hdr_cube);
    std::shared_ptr<TextureCube> specular_cube = precompute_ibl_specular(hdr_cube);
    return std::make_shared<ImageBasedLight>(specular_cube, SphericalHarmonics(diffuse_cube).coefficients, intensity);
}