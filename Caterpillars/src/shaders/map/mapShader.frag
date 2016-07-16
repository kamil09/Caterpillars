#version 330 core

in vec3 textCord;
in float towL1;
in float towL2;

in vec4 vN;
in vec4 vV;
in vec4 vL1;
in vec4 vL2;
in vec4 vL3;

out vec4 color;

uniform sampler3D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main(){
	vec4 De=vec4(0.1f,0.1f,0.1f,1.0f);
	vec4 Ld=vec4(1,1,1,1);
	//vec4 Ms=vec4(1,1,1,1);
	//vec4 Ls=vec4(1,1,1,1);

	vec4 mN=normalize(vN);
	vec4 mL1=normalize(vec4(vL1.xyz,1.0f));
	vec4 mL2=normalize(vec4(vL2.xyz,1.0f));
	vec4 mL3=normalize(vec4(vL3.xyz,1.0f));

	//vec4 mV=normalize(vec4(vV.xyz,1.0f));
	//vec4 mR1=reflect(-mL1,mN);
	//vec4 mR2=reflect(-mL2,mN);
	//vec4 mR3=reflect(-mL3,mN);

	vec4 shadow = texture(shadowMap, vec2(textCord.x,textCord.y));
	vec4 light = texture(lightMap,vec2(textCord.x,textCord.y));
	vec4 textu = texture(ourTexture1,textCord);

	vec4 Md=(3*textu + shadow)/4;
	Md=vec4(Md.xyz,1.0f);

	float nl1=max(0,dot(mN,mL1));
	float nl2=max(0,dot(mN,mL2));
	float nl3=max(0,dot(mN,mL3));

	color = (De*Md)+(Md*Ld*towL1*nl1)+(Md*Ld*towL2*nl2)+(Md*Ld*nl3);
}
