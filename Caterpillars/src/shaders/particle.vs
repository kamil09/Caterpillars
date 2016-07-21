#version 330 core

uniform mat4 P;
uniform mat4 V;

out vec2 textCord;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 las;
layout (location = 2) in vec2 texture;

void main(){
   mat4 scl=mat4(las.a,0,0,0,
                  0,las.a,0,0,
                  0,0,las.a,0,
                  0,0,0,1);
   mat4 pos=mat4(1,0,0,las.x,
                 0,1,0,las.y,
                 0,0,1,las.z,
                 0,0,0,1);
   mat4 M=pos*scl;

	gl_Position = P*V*M*vec4(vertex.x, vertex.y, vertex.z, 1.0);
	textCord = texture;
}
