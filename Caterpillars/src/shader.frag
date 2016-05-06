#version 330 core

smooth in vec3 thePosition;
out vec4 color;

//uniform vec4 buttonColor;

void main(){
	color = vec4(0.5, thePosition.y/600.0, 0.0, 1.0);
}
