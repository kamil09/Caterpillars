#version 330 core

in vec2 TexCoord;
in vec2 iTexCoord;
in float towL1;
in float towL2;
flat in int czyNormalMapI;

in vec4 vN;
in vec4 vV;
in vec4 vL1;
in vec4 vL2;
in vec4 vL3;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;
uniform sampler2D normalMap;

void main(){
	vec4 De=vec4(0.1f,0.1f,0.1f,1.0f);
	vec4 Ld=vec4(1,1,1,1);
	vec4 Ms=vec4(1,1,1,1);
	vec4 Ls=vec4(1,1,1,1);

	vec4 mN=normalize(vec4(vN.xyz,1.0f));
	vec4 mL1=normalize(vec4(vL1.xyz,1.0f));
	vec4 mL2=normalize(vec4(vL2.xyz,1.0f));
	vec4 mL3=normalize(vec4(vL3.xyz,1.0f));
	vec4 mV=normalize(vec4(vV.xyz,1.0f));

	vec4 mR1=reflect(-mL1,mN);
	vec4 mR2=reflect(-mL2,mN);
	vec4 mR3=reflect(-mL3,mN);

	vec4 shadow = texture(shadowMap,TexCoord);
	vec4 light = texture(lightMap,TexCoord);
	vec4 textu = texture(ourTexture1,TexCoord);
	float refCoef = (light.x+light.y+light.z)/3;

	vec4 Md=(3*textu + shadow)/4;
	float sunCoef=0.8f;

	if(czyNormalMapI == 1){
		vec4 normalMapV = texture(normalMap,TexCoord);
		normalMapV = vec4(2*normalMapV.xyz-1,0);
		float sunCoef=1.0f;
		mN=normalize(normalMapV);
	}
	Md=vec4(Md.xyz,1.0f);

	float nl1=max(0,dot(mN,mL1));
	float nl2=max(0,dot(mN,mL2));
	float nl3=max(0,dot(mN,mL3));

	int shininess=350;
	float rv1=pow(max(0,dot(mR1,mV)),shininess);
	float rv2=pow(max(0,dot(mR2,mV)),shininess);
	float rv3=pow(max(0,dot(mR3,mV)),shininess);

	color=(De*Md)+(Md*Ld*towL1*nl1*0.8)+(Md*Ld*towL2*nl2*0.8)+(Md*Ld*nl3*sunCoef)+(Ms*Ls*refCoef*towL1*rv1*0.9)+(Ms*Ls*towL2*refCoef*rv2*0.9)+(Ms*Ls*refCoef*rv3*0.6);
}
