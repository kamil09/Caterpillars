#version 330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 L;
uniform vec4 SUN;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec4 vN; //interpolowany wektor normalny w przestrzeni oka
out vec4 vV; //interpolowany wektor do obserwatora w przestrzeni oka
out vec4 vL1; //interpolowany wektor do zrodla swiatla 1 w przestrzeni oka
out vec4 vL2; //interpolowany wektor do zrodla swiatla 2 w przestrzeni oka
out vec4 vL3; //interpolowany wektor do zrodla swiatla 3 w przestrzeni oka

out float vLD1;//Mnożnik reflektoru zalezny od kierunku padania światła
out float vLD2;//Mnożnik reflektoru zalezny od kierunku padania światła

out vec2 TexCoord;

float calcLightMul(vec4 Lpos, vec4 Ldir, vec3 pos){
	float val=0;
	vec3 LposV = vec3(Lpos.x,Lpos.y,Lpos.z);
	vec3 LdirV = normalize(vec3(Ldir.x,Ldir.y,Ldir.z));
	vec3 MdirV = normalize(pos-LposV);
	float LD = sqrt( (LdirV.x*LdirV.x)+(LdirV.y*LdirV.y)+(LdirV.z*LdirV.z) );
   float MD = sqrt( (MdirV.x*MdirV.x)+(MdirV.y*MdirV.y)+(MdirV.z*MdirV.z) );
   float cosK;
   cosK= ((LdirV.x*MdirV.x) + (LdirV.y*MdirV.y) + (LdirV.z*MdirV.z)) / (LD*MD);
   float kat = -acos(cosK);
	if(kat<0) kat*=-1;
	if(kat < 50*3.14/360) val=1;
	return val;
}

void main(){
	vec4 L1pos = normalize(L[0]);
	vec4 L2pos = normalize(L[2]);
	vec4 L1dir = normalize(L[1]);
	vec4 L2dir = normalize(L[3]);

	vec4 vertex = vec4(position.x, position.y, position.z, 1.0f);
	vN=normalize(V*M*vec4(normal.xyz,1.0f)); //Oblicz i interpoluj wektor normalny w przestrzeni oka
	vL1=normalize(V*L1pos-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL2=normalize(V*L2pos-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL3=normalize(V*SUN-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vV=normalize(vec4(0,0,0,1)-V*M*vertex); //Oblicz i interpoluj wektor do obserwatora w przestrzeni oka

	vLD1 = calcLightMul(L1pos,L1dir,position);
	vLD2 = calcLightMul(L2pos,L2dir,position);

	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	gl_Position = P*V*M*vertex;

}
