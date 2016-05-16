#version 330 core

in vec3 textCord;
out vec4 color;

uniform sampler3D ourTexture1;

void main(){
	color = texture(ourTexture1,textCord);
}
