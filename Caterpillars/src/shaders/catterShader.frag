#version 330 core

in vec2 TexCoord;
in vec4 vN;
in vec4 vV;
in vec4 vL1;
in vec4 vL2;
in vec4 vL3;
in float vLD1;
in float vLD2;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main(){
	vec4 De=vec4(0.15f,0.15f,0.15f,1.0f);
	vec4 Ld=vec4(1,1,1,1);
	vec4 Ms=vec4(1,1,1,1);
	vec4 Ls=vec4(1,1,1,1);

	vec4 mN=normalize(vN);
	vec4 mL1=normalize(vL1);
	vec4 mL2=normalize(vL2);
	vec4 mL3=normalize(vL3);
	vec4 mV=normalize(vV);
	vec4 mR1=reflect(-mL1,mN);
	vec4 mR2=reflect(-mL2,mN);
	vec4 mR3=reflect(-mL3,mN);

	vec4 shadow = texture(shadowMap,TexCoord);
	vec4 light = texture(lightMap,TexCoord);
	vec4 textu = texture(ourTexture1,TexCoord);

	vec4 Md=(3*textu + shadow)/4;

	float nl1=max(0,dot(mN,mL1));
	float nl2=max(0,dot(mN,mL2));

	color=(Md*De) + (( (Md*Ld*nl1*vLD1) + (Md*Ld*nl2*vLD2) )*(vec4(1)-De) );
}
