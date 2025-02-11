layout (location = 0) in vec3 POSITION;
uniform mat4 iMVP;
out V2F {
    vec3 worldPos;
} o;
void main()
{
    vec4 worldPos = vec4(POSITION, 1.f);
    o.worldPos = worldPos.xyz;
    gl_Position = iMVP * worldPos;
}