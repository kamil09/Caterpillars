#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

out vec3 textCord;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texture;

void main(){
	gl_Position = projectionMatrix*modelViewMatrix*vec4(position.x, position.y, position.z, 1.0);
	//textCord = vec3(texture.x,texture.y,texture.z);
	textCord = texture;
}
