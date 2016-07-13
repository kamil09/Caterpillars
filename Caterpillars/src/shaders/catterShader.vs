#version 330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 L;
uniform vec3 SUN;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec4 vN; //interpolowany wektor normalny w przestrzeni oka
out vec4 vV; //interpolowany wektor do obserwatora w przestrzeni oka
out vec4 vL1; //interpolowany wektor do zrodla swiatla 1 w przestrzeni oka
out vec4 vL2; //interpolowany wektor do zrodla swiatla 2 w przestrzeni oka
out vec4 vL3; //interpolowany wektor do zrodla swiatla 3 w przestrzeni oka

out vec2 TexCoord;

void main(){
	vec4 vertex = vec4(position.x, position.y, position.z, 1.0f);

	vN=normalize(V*M*vec4(normal.xyz,1.0f)); //Oblicz i interpoluj wektor normalny w przestrzeni oka
	vL1=normalize(V*L[0]-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL2=normalize(V*L[2]-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vL3=normalize(V*vec4(SUN.xyz,1.0f)-V*M*vertex); //Oblicz i interpoluj wektor do zrodla swiatla w przestrzeni oka
	vV=normalize(vec4(0,0,0,1)-V*M*vertex); //Oblicz i interpoluj wektor do obserwatora w przestrzeni oka

	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	gl_Position = P*V*M*vertex;

}
