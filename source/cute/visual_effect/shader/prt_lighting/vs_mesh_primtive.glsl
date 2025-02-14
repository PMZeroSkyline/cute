layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec3 NORMAL;
layout (location = 2) in vec4 TANGENT;
layout (location = 3) in vec2 TEXCOORD_0;
layout (location = 4) in vec2 TEXCOORD_1;
layout (location = 5) in vec2 TEXCOORD_2;
layout (location = 6) in vec2 TEXCOORD_3;
layout (location = 7) in vec3 COLOR_0;
layout (location = 8) in vec4 JOINTS_0;
layout (location = 9) in vec4 WEIGHTS_0;
layout (location = 10) in mat4 INSTANCE;
uniform mat4 iM;
#ifdef SKINNING
uniform mat4 iJ[128];
#endif
#include "../lib/camera_block.glsl"
out V2F {
    vec3 worldPos;
    vec2 texcoord0;
    vec3 world_normal;
} o;
void main() {
#ifdef SKINNING
    mat4 M = WEIGHTS_0[0] * iJ[int(JOINTS_0[0])] + 
             WEIGHTS_0[1] * iJ[int(JOINTS_0[1])] + 
             WEIGHTS_0[2] * iJ[int(JOINTS_0[2])] + 
             WEIGHTS_0[3] * iJ[int(JOINTS_0[3])];
#else
    mat4 M = iM;
#endif
#ifdef INSTANCING
    M = M * INSTANCE;
#endif
    vec4 world_pos = M * vec4(POSITION, 1.f);
    mat3 MIT = transpose(inverse(mat3(M)));
    vec3 world_normal = normalize(MIT * NORMAL);
    o.worldPos = world_pos.xyz;
    o.texcoord0 = TEXCOORD_0;
    o.world_normal = world_normal;
    gl_Position = iP * iV * world_pos;
}