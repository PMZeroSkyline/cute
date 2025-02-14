out vec2 FragColor;
in V2F {
    vec2 texcoord0;
} i;
#include "../lib/integrate_brdf.glsl"

void main() 
{
    FragColor = integrate_brdf(i.texcoord0.x, i.texcoord0.y);
}