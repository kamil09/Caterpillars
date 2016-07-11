#version 330 core

in vec3 textCord;
in float towL1;
in float towL2;

out vec4 color;

uniform sampler3D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main(){
	vec4 shadow = texture(shadowMap, vec2(textCord.x,textCord.y));
	vec4 light = texture(lightMap,vec2(textCord.x,textCord.y));

//	color = texture(ourTexture1,textCord);
	color = (texture(ourTexture1,textCord)*3/5)+(vec4(1,1,1,0)*1/5*towL1)+(vec4(1,1,1,0)*1/5*towL2);


}
