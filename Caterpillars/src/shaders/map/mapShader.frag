#version 330 core

smooth in vec3 thePosition;
in vec3 textCord;
out vec4 color;

//uniform vec4 buttonColor;
uniform sampler3D ourTexture1;

void main(){
	//color = vec4(0.5, thePosition.y/600.0, 0.0, 1.0);
	color = texture(ourTexture1,textCord);
}
