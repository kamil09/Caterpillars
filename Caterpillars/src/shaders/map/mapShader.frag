#version 330 core

in vec3 textCord;
in float towL1;
in float towL2;

out vec4 color;

uniform sampler3D ourTexture1;

void main(){
//	color = texture(ourTexture1,textCord);
	color = (texture(ourTexture1,textCord)*3/5)+(vec4(1,1,1,0)*1/5*towL1)+(vec4(1,1,1,0)*1/5*towL2);
}
