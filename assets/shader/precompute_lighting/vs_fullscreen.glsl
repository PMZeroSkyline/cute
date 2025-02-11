layout (location = 0) in vec3 POSITION;
layout (location = 3) in vec2 TEXCOORD_0;

out V2F {
    vec2 texcoord0;
} o;

void main()
{
    o.texcoord0 = TEXCOORD_0;
    gl_Position = vec4(POSITION, 1.f);
}