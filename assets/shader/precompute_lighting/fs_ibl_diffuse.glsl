out vec4 FragColor;

in V2F {
    vec3 worldPos;
} i;
// https://learnopengl.com/PBR/Lighting
const float PI = 3.14159265359;
uniform samplerCube iEnvironmentTexture;
// https://www.khronos.org/opengl/wiki/Cubemap_Texture
vec3 cubemap_mapping(vec3 v)
{
    return vec3(v.x, v.z, v.y);
}
void main()
{
    vec3 irradiance = vec3(0.0);   

    vec3 N = normalize(i.worldPos);
    vec3 up = vec3(0.0, 0.0, 1.0);
    vec3 right = normalize(cross(up, N));
    up = normalize(cross(N, right));

    float sample_delta = 0.025;
    float nr_samples = 0.0f;
    for(float phi = 0.0; phi < 2.0 * PI; phi += sample_delta)
    {
        for(float theta = 0.0; theta <= 0.5 * PI; theta += sample_delta)
        {
            vec3 tangent_sample = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            vec3 sample_vec = tangent_sample.x * right + tangent_sample.y * up + tangent_sample.z * N;
            vec3 col = texture(iEnvironmentTexture, cubemap_mapping(sample_vec)).rgb;
            irradiance += col * cos(theta) * sin(theta);
            nr_samples++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(nr_samples));

    FragColor = vec4(irradiance, 1.0);
}