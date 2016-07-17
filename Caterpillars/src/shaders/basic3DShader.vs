#version 330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 L;
uniform vec4 SUN;
uniform int czyNormalMap;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec4 vN; //interpolowany wektor normalny w przestrzeni oka
out vec4 vV; //interpolowany wektor do obserwatora w przestrzeni oka
out vec4 vL1; //interpolowany wektor do zrodla swiatla 1 w przestrzeni oka
out vec4 vL2; //interpolowany wektor do zrodla swiatla 2 w przestrzeni oka
out vec4 vL3; //interpolowany wektor do zrodla swiatla 3 w przestrzeni oka
out float towL1;
out float towL2;
flat out int czyNormalMapI;

out vec2 TexCoord;

float calcLightMul(vec4 Lpos, vec4 Ldir, vec4 pos4){
	float val=0;
	vec3 pos = vec3(pos4.x,pos4.y,pos4.z);

	vec3 LposV = vec3(Lpos.x,Lpos.y,Lpos.z);
	vec3 LdirV = vec3(Ldir.x,Ldir.y,Ldir.z);
	vec3 MdirV = pos-LposV;
	float LD = sqrt( (LdirV.x*LdirV.x)+(LdirV.y*LdirV.y)+(LdirV.z*LdirV.z) );
   float MD = sqrt( (MdirV.x*MdirV.x)+(MdirV.y*MdirV.y)+(MdirV.z*MdirV.z) );
   float cosK;
   cosK= ((LdirV.x*MdirV.x) + (LdirV.y*MdirV.y) + (LdirV.z*MdirV.z)) / (LD*MD);
   float kat = acos(cosK);
	//W zależności od kąta pomiędzy wektorem do reflektora a wektorem kierunku reflektora
	if(abs(kat)<=0.4f ) val=1.0f;
	if(abs(kat)>=0.6f ) val=0.0f;
	if(abs(kat)>0.4f && abs(kat)<0.6f) val=1.0f-(abs(kat)*5.0f-2.0f);
	//W zalezności od długości wektora do reflektora
	if(MD>=500) val=0;
	if(MD<=400) val*=1;
	if(MD<=60) val=0;
	if( (MD>400) && (MD<500) ) val*=(1-((MD*10-4000)/1000));

	return val;
}

void main(){
	vec4 L1pos = V*L[0];
	vec4 L2pos = V*L[2];
	vec4 L1dir = V*L[1];
	vec4 L2dir = V*L[3];
	vec4 SUN2 = V*SUN;

	vec4 vertex = M*vec4(position.x, position.y, position.z, 1.0f);
	vec4 vertexO = V*vertex;
	vec4 nor = V*M*vec4(normal.xyz,1.0f);

	towL1 = calcLightMul(L[0],L[1],vertex);
	towL2 = calcLightMul(L[2],L[3],vertex);

	vN=normalize(-nor); //Oblicz i interpoluj wektor normalny w przestrzeni oka
	vL1=normalize(L1pos-vertexO); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL2=normalize(L2pos-vertexO); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL3=normalize(SUN2-vertexO); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vV=normalize(vec4(0,0,0,1)-vertexO); //Oblicz i interpoluj wektor do obserwatora w przestrzeni oka

	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	gl_Position = P*V*vertex;
	czyNormalMapI=czyNormalMap;
}
