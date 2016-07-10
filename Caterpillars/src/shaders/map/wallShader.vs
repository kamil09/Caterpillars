#version 330 core

uniform mat4 P;
uniform mat4 V;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 TexCoord;

void main(){
	gl_Position = P*V*vec4(position.x, position.y, position.z, 1.0);
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
