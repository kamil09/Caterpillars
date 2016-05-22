#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 M;

out vec2 TexCoord;

void main(){
	gl_Position = M*vec4(position.x, position.y, position.z, 1.0);
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
