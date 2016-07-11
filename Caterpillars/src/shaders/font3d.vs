#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 V;
uniform mat4 M;
void main()
{
    gl_Position = projection *V * M * vec4(vertex.xyz, 1.0);
    // gl_Position = vec4(vertex.xy, 0.0, 1.0);
    // TexCoords = vertex.zw;
    TexCoords = vec2(vertex.z,1-vertex.w);
}
