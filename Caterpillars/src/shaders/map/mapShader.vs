#version 330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 L;
uniform vec4 SUN;

out vec3 textCord;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texture;
layout (location = 2) in vec3 normal;

out vec4 vN; //interpolowany wektor normalny w przestrzeni swiata
out vec4 vL1; //interpolowany wektor do zrodla swiatla 1 w przestrzeni swiata
out vec4 vL2; //interpolowany wektor do zrodla swiatla 2 w przestrzeni swiata
out vec4 vL3; //interpolowany wektor do zrodla swiatla 3 w przestrzeni swiata
out float towL1;
out float towL2;

float calcLightMul(vec4 Lpos, vec4 Ldir, vec3 pos){
	float val=0;
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
	if( (MD>400) && (MD<500) ) val*=(1-((MD*10-4000)/1000));
	return val;
}

void main(){
	vec4 L1pos = L[0];
	vec4 L2pos = L[2];
	vec4 L1dir = L[1];
	vec4 L2dir = L[3];
	mat4 M = mat4(1);

	towL1 = calcLightMul(L1pos,L1dir,position);
	towL2 = calcLightMul(L2pos,L2dir,position);

	vec4 vertex = vec4(position.x, position.y, position.z, 1.0f);
	vN=normalize(vec4(normal.xyz,1.0f)); //Oblicz i interpoluj wektor normalny w przestrzeni swiata
	vL1=normalize(L1pos-vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni swiata
	vL2=normalize(L2pos-vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni swiata
	vL3=normalize(SUN-vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni swiata

	gl_Position = P*V*M*vec4(position.x, position.y, position.z, 1.0);
	textCord = texture;
}
