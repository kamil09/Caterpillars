#version 330 core

uniform mat4 P;
uniform mat4 V;

out vec2 textCord;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 las;
layout (location = 2) in vec2 texture;

void main(){
   mat4 scl=mat4(las[3],0.0f,0.0f,0.0f,
                  0.0f,las[3],0.0f,0.0f,
                  0.0f,0.0f,las[3],0.0f,
                  0.0f,0.0f,0.0f,1.0f);
   mat4 pos=mat4(1.0f,0.0f,0.0f,0.0f,
                 0.0f,1.0f,0.0f,0.0f,
                 0.0f,0.0f,1.0f,0.0f,
                 las[0],las[1],las[2],1.0f);
   mat4 M=pos*scl;

	gl_Position = P*V*M*vec4(vertex.x, vertex.y, vertex.z, 1.0);
	textCord = vec2(texture.x+((vertex.x+vertex.y)/20),texture.y+((vertex.y+vertex.z)/20));
}
