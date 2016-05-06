#include "object.hpp"

Object::Object(){
	this->buffersCount = 0;
	this->verticesCount = 0;
	this->indicesCount = 0;

	this->windMul=0;
	this->speedX=0;
	this->speedY=0;
	this->speedZ=0;
	this->kickTime=0;
	this->canKick=true;
}
Object::~Object(){

}

void Object::draw(){

};

void Object::kick(float x,float y, float z){
	this->speedX=x;
	this->speedY=y;
	this->speedZ=z;
	//this->kickTime=time_now??;

}
void Object::recalculatePhysics(){
	//this->kickTime=???
	//Wzorek na rzut ukośny mając prędkości początkowe i czas wyliczamy nowe współrzędne
	//Sprawdzanie kolizji (czy można przesunąć obiekt na daną pozycję)

}

void Object::initBinding(){
	std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
	this->buffersCount++;
	this->buffers.push_back(new Buffers());
	if(this->buffers.empty()){
		std::cerr << "ERROR::EMPTY BUFFER::ERROR" << std::endl;
	}

	glGenVertexArrays(1, &this->buffers.back()->VAO);
	glGenBuffers(1, &this->buffers.back()->VBO);
	glGenBuffers(1, &this->buffers.back()->EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->buffers.back()->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers.back()->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.back()->EBO);

}


void Object::bindTexture2D(const GLchar *texturePath){
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	this->loadTexture2D(texturePath);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Object::loadTexture2D(const GLchar *texturePath){
	this->image = SOIL_load_image(texturePath, &this->textureWidth, &this->textureHeight, 0, SOIL_LOAD_RGB);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
}

GLfloat Object::getPosX(){
	return this->posX;
}
void Object::setPosX(GLfloat newValue){
	this->posX = newValue;
}

GLfloat Object::getPosY(){
	return this->posY;
}
void Object::setPosY(GLfloat newValue){
	this->posY = newValue;
}

GLfloat Object::getPosZ(){
	return this->posZ;
}
void Object::setPosZ(GLfloat newValue){
	this->posZ = newValue;
}
