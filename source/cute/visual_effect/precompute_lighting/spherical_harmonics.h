#ifndef SPHERICAL_HARMONICS_H
#define SPHERICAL_HARMONICS_H

#include "core/math/vec3.h"
#include <array>
#include "renderer/texture_cube.h"

// https://metashapes.com/blog/realtime-image-based-lighting-using-spherical-harmonics/
struct SphericalHarmonics
{
	struct Sample
	{
		int side;
		int x;
		int y;
		double coefficients[9];
	};
	std::array<vec3, 9> coefficients;
	std::vector<Sample> samples;
    SphericalHarmonics() = default;
    SphericalHarmonics(const std::shared_ptr<TextureCube>& tex);
	void create_for_cubeMap(int resolutionX, int resolutionY);
	void sample_cube_map(std::function<vec3(int, int, int)> func);
	void evaluate_cube_map(std::function<void(int const, int const, int const, vec3 const)> func) const;
};

#endif