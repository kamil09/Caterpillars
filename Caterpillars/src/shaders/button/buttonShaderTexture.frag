#version 330 core
// in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform vec4 uColor;
uniform int check;
// uniform sampler2D ourTexture2;

void main(){
    int temp = check;
    if(temp != 0){
	    color = texture(ourTexture1, TexCoord)*uColor;
    }
    else{
        color = uColor;
    }
}
