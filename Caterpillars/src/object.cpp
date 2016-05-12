#include "object.hpp"

Object::Object(){
	this->currentBinding = 0;
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

Object::~Object(){}

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




void Object::initBinding(bool newBuffer){
	if(newBuffer == true){
		this->newBinding();
	}
	else{
		// std::cout << "HEJ!" << std::endl;
		this->buffers[currentBinding]->usuwanie();
	}
	// if(this->currentBinding!=0){
	// 	std::cout << "kurcze" << std::endl;
	// }
	glGenVertexArrays(1, &this->buffers[this->currentBinding]->VAO);
	glGenBuffers(1, &this->buffers[this->currentBinding]->VBO);
	glGenBuffers(1, &this->buffers[this->currentBinding]->EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->buffers[this->currentBinding]->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[this->currentBinding]->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[this->currentBinding]->EBO);
	// std::cout << "hej" << std::endl;
}

void Object::newBinding(){
	if(buffersCount > 5){
		Buffers *temp = this->buffers[0];
		this->buffers.erase(this->buffers.begin()+0);
		delete temp;
		this->buffersCount--;
	}
	// std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
	this->buffersCount++;
	this->buffers.push_back(new Buffers());
	if(this->buffers.empty()){
		std::cerr << "ERROR::EMPTY BUFFER::ERROR" << std::endl;
	}
	// if(this->buffersCount==1){
	// 	this->currentBinding = 0;
	// }
	// else{
		this->currentBinding = this->buffersCount-1;
	// }
}

GLuint Object::currentVAO(){
	return this->buffers[this->currentBinding]->VAO;
}



void Object::endBinding(){
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
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
	// std::cout << "hej" << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// errorCheck("Po loadTexture");
}

void Object::loadTexture2D(const GLchar *texturePath){
	std::vector<unsigned char> image;
	unsigned width,height;
	unsigned error = lodepng::decode(image,width,height,texturePath);
	if(error != 0){
		std::cout << "ERROR:: " << error << std::endl;
	}
	// std::cout << "Texture width: " << width << " texture height: " << height << std::endl;
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	errorCheck("Po loadTexture");
	glGenerateMipmap(GL_TEXTURE_2D);

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
