#version 330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 L;

out vec3 textCord;
out float towL1;
out float towL2;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texture;

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

	//float diff = sqrt(pow(MdirV.x-LdirV.x,2)+pow(MdirV.y-LdirV.y,2)+pow(MdirV.z-LdirV.z,2));

	//if( diff < 0.4) val=1;
	//else val = diff/2;
	//val=1-diff;
	//if(val>0.8) val=1;
	//if(val<0.5) val=0;
	if(kat < 50*2*3.14/360) val=1;

	return val;
}

void main(){

	vec4 L1pos = L[0];
	vec4 L2pos = L[2];
	vec4 L1dir = L[1];
	vec4 L2dir = L[3];

	towL1 = 0.0f;
	towL2 = 0.0f;
	towL1 = calcLightMul(L1pos,L1dir,position);
	towL2 = calcLightMul(L2pos,L2dir,position);

	gl_Position = P*V*vec4(position.x, position.y, position.z, 1.0);
	textCord = texture;
}
