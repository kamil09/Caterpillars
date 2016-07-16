#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 V;
uniform mat4 M;
void main()
{
//    mat4 View =V;
//    View[0][0] = 1.0f;
//    View[0][1] = 0.0f;
//    View[0][2] = 0.0f;
//
//    View[1][0] = 0.0f;
//    View[1][1] = 1.0f;
//    View[1][2] = 0.0f;
//
//    View[2][0] = 0.0f;
//    View[2][1] = 0.0f;
//    View[2][2] = 1.0f;
//    gl_Position = projection *View * M * vec4(vertex.xyz, 1.0);

    gl_Position = projection * V * vec4(vec3(M[3][0],M[3][1],M[3][2]),1.0f);
//    gl_Position = projection *V * M * vec4(vertex.xyz, 1.0);
    gl_Position /= gl_Position.w;
    gl_Position.xy += vertex.xy * vec2(0.015,0.015);
    // gl_Position = vec4(vertex.xy, 0.0, 1.0);
    // TexCoords = vertex.zw;
    TexCoords = vec2(vertex.z,vertex.w);
}
