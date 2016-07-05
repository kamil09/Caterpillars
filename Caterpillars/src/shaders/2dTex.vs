#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 M;
uniform mat4 P;
out vec2 TexCoord;

void main(){
	//gl_Position = P*M*vec4(position.x, position.y, 1.0, 1.0);
	gl_Position = P*M*vec4(position.x, position.y, 0.0, 1.0);
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
