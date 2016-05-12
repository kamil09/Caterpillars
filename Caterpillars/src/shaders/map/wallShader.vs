#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

layout (location = 0) in vec3 position;

void main(){
	gl_Position = projectionMatrix*modelViewMatrix*vec4(position.x, position.y, position.z, 1.0);
}
