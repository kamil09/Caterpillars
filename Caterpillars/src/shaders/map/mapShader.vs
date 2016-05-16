#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

smooth out vec3 thePosition; // Interpolate position among fragments
out vec3 textCord;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texture;
void main(){
	gl_Position = projectionMatrix*modelViewMatrix*vec4(position.x, position.y, position.z, 1.0);
	thePosition = posit		ion;
	textCord = texture;
}
