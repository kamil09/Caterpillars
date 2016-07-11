#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main(){
	color = texture(ourTexture1,TexCoord);
	vec4 shadow = texture(shadowMap,TexCoord);
	vec4 light = texture(lightMap,TexCoord);
	
   //color = vec4(1.0f,0.0f,0.0f,0.5f);
}
