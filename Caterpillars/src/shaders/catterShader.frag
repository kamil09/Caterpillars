#version 330 core

in vec2 TexCoord;
in vec4 vN; //interpolowany wektor normalny w przestrzeni oka
in vec4 vV; //interpolowany wektor do obserwatora w przestrzeni oka
in vec4 vL1; //interpolowany wektor do zrodla swiatla 1 w przestrzeni oka
in vec4 vL2; //interpolowany wektor do zrodla swiatla 2 w przestrzeni oka
in vec4 vL3; //interpolowany wektor do zrodla swiatla 3 w przestrzeni oka
in vec4 vLD1;	//wektor kierunku światła 1
in vec4 vLD2; //wektor kierunku światła 2

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main(){
	vec4 Ma=vec4(0.2f,0.2f,0.2f,1);
	vec4 La=vec4(0.2f,0.2f,0.2f,1);
	vec4 Ld=vec4(1,1,1,1);
	vec4 Ms=vec4(1,1,1,1);
	vec4 Ls=vec4(1,1,1,1);

	// vec4 mN=normalize(vN);
	// vec4 mL1=normalize(vL1);
	// vec4 mL2=normalize(vL2);
	// vec4 mL3=normalize(vL3);
	// vec4 mV=normalize(vV);
	// vec4 mR1=reflect(-mL1,mN);
	// vec4 mR2=reflect(-mL2,mN);
	// vec4 mR3=reflect(-mL3,mN);

	// vec4 shadow = texture(shadowMap,TexCoord);
	// vec4 light = texture(lightMap,TexCoord);
	// vec4 Md=(3*texture(ourTexture1,TexCoord) + texture(shadowMap,TexCoord))/4;
	//
	// float shininess=50;
	// float nl=max(0,dot(mN,mL3));
	// float rv=pow(max(0,dot(mN,mL3)),shininess);

	//color=Ma*La+Md*Ld*nl+Ms*Ls*rv;
	color=texture(ourTexture1,TexCoord);
}
