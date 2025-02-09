#include "spherical_harmonics.h"

SphericalHarmonics::SphericalHarmonics(const std::shared_ptr<TextureCube>& tex)
{
    create_for_cubeMap(tex->mipmaps[0][0]->x, tex->mipmaps[0][0]->y);
    if (tex->mipmaps[0][0]->type == GL_UNSIGNED_BYTE)
    {
        sample_cube_map([&tex](int i, int x, int y){
            u8vec3 color = *(u8vec3*)(*tex->mipmaps[0][i])(x, y);
            return vec3(color) / 255.f;
        });
    }
    else if (tex->mipmaps[0][0]->type == GL_FLOAT)
    {
        sample_cube_map([&tex](int i, int x, int y){
            return *(vec3*)(*tex->mipmaps[0][i])(x, y);
        });
    }
}
void SphericalHarmonics::create_for_cubeMap(int resolutionX, int resolutionY)
{
    samples.clear();
	for (int side = 0; side < 6; ++side)
	{
		for (int y = 0; y < resolutionY; ++y)
		{
			for (int x = 0; x < resolutionX; ++x)
			{
				vec2 uv((float)x / (float)(resolutionX - 1) * 2.0f - 1.0f, (float)y / (float)(resolutionY - 1) * 2.0f - 1.0f);
				vec3 direction;
				if (side == 0)
				{
					direction = vec3(1.f, uv.y, uv.x);
				}
				else if (side == 1)
				{
					direction = vec3(-1.f, uv.y, -uv.x);
				}
				else if (side == 2)
				{
					direction = vec3(uv.x, 1.f, uv.y);
				}
				else if (side == 3)
				{
					direction = vec3(uv.x, -1.f, -uv.y);
				}
				else if (side == 4)
				{
					direction = vec3(uv.x, uv.y, -1.f);
				}
				else if (side == 5)
				{
					direction = vec3(-uv.x, uv.y, 1.f);
				}
				direction = normalize(direction);
				Sample sample;
				sample.side = side;
				sample.x = x;
				sample.y = y;
				sample.coefficients[0] = 0.282095;
				sample.coefficients[1] = 0.488603 * direction.y;
				sample.coefficients[2] = 0.488603 * direction.z;
				sample.coefficients[3] = 0.488603 * direction.x;
				sample.coefficients[4] = 1.092548 * direction.x * direction.y;
				sample.coefficients[5] = 1.092548 * direction.y * direction.z;
				sample.coefficients[6] = 0.315392 * (3.0 * direction.z * direction.z - 1.0);
				sample.coefficients[7] = 1.092548 * direction.x * direction.z;
				sample.coefficients[8] = 0.546274 * (direction.x * direction.x - direction.y * direction.y);
				samples.push_back(sample);
			}
		}
	}
}
void SphericalHarmonics::sample_cube_map(std::function<vec3(int, int, int)> func)
{
    memset(coefficients.data(), 0, coefficients.size() * sizeof(vec3));
	for (const auto& sample : samples)
	{
		const auto& value = func(sample.side, sample.x, sample.y);
		for (int i = 0; i < 9; ++i)
		{
			coefficients[i] += value * sample.coefficients[i];
		}
	}
	double factor = 4.0 * PI / (double)samples.size();
	for (int i = 0; i < 9; ++i)
	{
		coefficients[i] *= factor;
	}
}
void SphericalHarmonics::evaluate_cube_map(std::function<void(int const, int const, int const, vec3 const)> func) const
{
	for (const auto& sample : samples)
	{
		vec3 value;
		for (int i = 0; i < 9; ++i)
		{
			value += sample.coefficients[i] * coefficients[i];
		}
		func(sample.side, sample.x, sample.y, value);
	}
}