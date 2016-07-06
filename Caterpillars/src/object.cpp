#include "object.hpp"
#include "state/game/map/map.hpp"
#include "state/game/game.hpp"

Object::Object(){
	this->teksturCount = 0;


	this->currentBinding = 0;
	this->buffersCount = 0;
	this->verticesCount = 0;
	this->indicesCount = 0;

	this->windMul=0;
	this->speed.x=0;
	this->speed.y=0;
	this->speed.z=0;
	this->kickTime=0;
	this->canKick=true;
	this->size = glm::vec3(1.0f);
	this->alpha = 1.0f;
}

Object::~Object(){
}

void Object::recalculateMatrix(){
	this->rotM = glm::mat4(1);
	this->sclM = glm::mat4(1);
	this->posM = glm::mat4(1);
	this->sclM[0][0]=this->scl.x;
	this->sclM[1][1]=this->scl.y;
	this->sclM[2][2]=this->scl.z;
	this->posM[3][0]=this->pos.x;
	this->posM[3][1]=this->pos.y;
	this->posM[3][2]=this->pos.z;
	glm::mat4 rotX = glm::mat4(
		glm::vec4(1.0f,0.0f,0.0f,0.0f),
		glm::vec4(0.0f,cos(this->rot.x),-sin(this->rot.x),0.0f),
		glm::vec4(0.0f,sin(this->rot.x), cos(this->rot.x),0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
	);
	this-> rotMY = glm::mat4(
		glm::vec4(cos(this->rot.y),0.0f, sin(this->rot.y),0.0f),
		glm::vec4(0.0f,1.0f,0.0f,0.0f),
		glm::vec4(-sin(this->rot.y),0.0f,cos(this->rot.y),0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
	);
	glm::mat4 rotZ = glm::mat4(
		glm::vec4(cos(this->rot.z),-sin(this->rot.z),0.0f,0.0f),
		glm::vec4(sin(this->rot.z), cos(this->rot.z),0.0f,0.0f),
		glm::vec4(0.0f,0.0f,1.0f,0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
	);
	this->rotM=this->rotMY*rotZ*rotX;

}
void Object::kick(float x,float y, float z){
	this->speed.x=x;
	this->speed.y=y;
	this->speed.z=z;
	//this->kickTime=time_now??;

}
void Object::recalculatePhysics(){
	//this->kickTime=???
	//Wzorek na rzut ukośny mając prędkości początkowe i czas wyliczamy nowe współrzędne
	//Sprawdzanie kolizji (czy można przesunąć obiekt na daną pozycję)


}

void Object::recalculateGravity(){
	//Tu bedzie wszystko zwiazanego z grawitacja

   //Tu trzeba bedzie na biezaca liczyc predkosc speedY
	//speedY > 0 oznaczac bedzie ruch w gore a < 0 spadanie
	//Nie mam pojecia czy to jest dobra koncepcja

	//cout<<endl<<endl<<"WYWOLANIE"<<endl;

	//cout << "PosX: " << this->pos.x << "  SpeedX: "<< this->speed.x << endl;
	//cout << "PosY: " << this->pos.y << "  SpeedY: "<< this->speed.y << endl;
	//cout << "PosZ: " << this->pos.z << "  SpeedZ: "<< this->speed.z << endl;



	end = clock();
	diff = ((float)end - (float)start);
	bet_time = diff/CLOCKS_PER_SEC;
	//cout<<"bet_time: "<< bet_time<<endl;
	in_meter = 10;//ile jednostek mamy w pseudo metrze
	if(sec_time)
	{
		if(!Game::checkCollisionAndMove(this, this->pos.x, this->pos.y, this->pos.z)){
			//gdy mamy kolizje obiektu z mapa
			//cout << ""Mapa - kolizja" << endl;
			this->pos.y = Map::getInstance().mapVert[(int)this->pos.x][(int)this->pos.z] + this->size.y + 1;
			this->on_the_ground = true;
			if(!this->speed.x || !this->speed.x || !this->speed.x) // zerowanie predkosci po opadnieciu na mape
			{
				this->speed.x = 0;
				this->speed.y = 0;
				this->speed.z = 0;
			}
		}
		else if(Game::checkCollisionAndMove(this, this->pos.x, this->pos.y, this->pos.z)) {

			if(!this->on_the_ground)
			{
				windX = 10 * bet_time * Map::getInstance().windForce.x * this->windMul;
				windY = bet_time * Map::getInstance().windForce.y * this->windMul;
				windZ = 10 * bet_time * Map::getInstance().windForce.z * this->windMul;
				//cout << windMul;
				//tutaj nalezy uwzglednic jeszcze sile wiatru
				this->speed.x +=  windX;//*windMul
				this->speed.z +=  windZ;//*windMul

			}


			this->speed.y -= Map::getInstance().gravity * bet_time* in_meter -
				windY;

			nextX = this->pos.x + this->speed.x;
			nextY = this->pos.y + this->speed.y;
			nextZ = this->pos.z + this->speed.z;

			if(!Game::checkCollisionAndMove(this, nextX, nextY, nextZ))
			{
				this->speed.x = 0;
				this->speed.y = 0;
				this->speed.z = 0;
				this->on_the_ground = true;
			}


			if(!this->on_the_ground)
			{
				this->speed.x -= windX;
				this->speed.y -= windY;
				this->speed.z -= windZ;
			}

		}
	}
	start = clock();
	sec_time = true;



}


void Object::diagonalThrow(glm::vec3 throw_speed){
	this->on_the_ground = false;
	this->speed.x = throw_speed.x;
	this->speed.y = throw_speed.y;
	this->speed.z = throw_speed.z;
}


//void Object::initBinding(bool newBuffer){
//	if(newBuffer == true) {
//		this->newBinding();
//	}
//	else{
//		// std::cout << "HEJ!" << std::endl;
//		this->buffers[currentBinding]->usuwanie();
//	}
//	// if(this->currentBinding!=0){
//	//      std::cout << "kurcze" << std::endl;
//	// }
//	glGenVertexArrays(1, &this->buffers[this->currentBinding]->VAO);
//	glGenBuffers(1, &this->buffers[this->currentBinding]->VBO);
//	glGenBuffers(1, &this->buffers[this->currentBinding]->EBO);
//	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//	glBindVertexArray(this->buffers[this->currentBinding]->VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[this->currentBinding]->VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[this->currentBinding]->EBO);
//	// std::cout << "hej" << std::endl;
//}

void Object::initBinding(){
	if(this->buffers.empty()) {
		this->buffersCount++;
		this->buffers.push_back(new Buffers());
		if(this->buffers.empty()) {
			std::cerr << "ERROR::EMPTY BUFFER::ERROR" << std::endl;
		}
		this->currentBinding = this->buffersCount-1;
	}
	else{
		this->buffers[currentBinding]->usuwanie();
	}
	glGenVertexArrays(1, &this->buffers[this->currentBinding]->VAO);
	glGenBuffers(1, &this->buffers[this->currentBinding]->VBO);
	glGenBuffers(1, &this->buffers[this->currentBinding]->EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->buffers[this->currentBinding]->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[this->currentBinding]->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[this->currentBinding]->EBO);
}

void Object::newBinding(){
	if(buffersCount > 5) {
		Buffers *temp = this->buffers[0];
		this->buffers.erase(this->buffers.begin()+0);
		delete temp;
		this->buffersCount--;
	}
	// std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
	this->buffersCount++;
	this->buffers.push_back(new Buffers());
	if(this->buffers.empty()) {
		std::cerr << "ERROR::EMPTY BUFFER::ERROR" << std::endl;
	}
	// if(this->buffersCount==1){
	//      this->currentBinding = 0;
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


void Object::paramText2D(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void Object::bindTexture2D(const GLchar *texturePath){
	glGenTextures(1, &this->texture2D);
	glBindTexture(GL_TEXTURE_2D, this->texture2D); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
// Set our texture parameters

	this->paramText2D();
	this->loadTexture2D(texturePath);
	// std::cout << "hej" << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// errorCheck("Po loadTexture");
}

void Object::loadTexture2D(const GLchar *texturePath){
	std::vector<unsigned char> image;
	unsigned width,height;
	unsigned error = lodepng::decode(image,width,height,texturePath);
	if(error != 0) {
		std::cout << "ERROR:: " << error << std::endl;
	}
	// std::cout << "Texture width: " << width << " texture height: " << height << std::endl;
	// std::cout << "0: " << image.data() << std::endl;
	//std::cout << "0: " << image.size() << std::endl;
	//std::cout << "1: " << image[1] << std::endl;
	//std::cout << "2: " << image[2] << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	errorCheck("Po loadTexture");
	glGenerateMipmap(GL_TEXTURE_2D);

}

void Object::bindTexture3D(int number,GLchar *texturePath[]){

	glGenTextures(1, &this->texture3D);
	glBindTexture(GL_TEXTURE_3D, this->texture3D); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	//Set our texture parameters
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER); // Set texture wrapping to GL_REPEAT
	// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	// Set texture filtering
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	listaTekstur.resize(number);
	for( int i=0;i<number;i++ ) this->listaTekstur[i].texturePath = texturePath[i];

	this->loadTexture3D(number);
	glBindTexture(GL_TEXTURE_3D, 0);
	errorCheck("Po loadTexture");
}

void Object::loadTexture3D(int number){
	int i;
	this->teksturCount = number;
	for(i=0; i < number; i++) {
		//std::cout << this->listaTekstur[i].texturePath << std::endl;
		// std::vector<unsigned char> image;
		unsigned int width,height;
		unsigned error = lodepng::decode(this->listaTekstur[i].image,width,height,this->listaTekstur[i].texturePath);
		if(error != 0) {
			std::cout << "ERROR:: " << error << std::endl;
		}
		this->listaTekstur[i].textureWidth = width;
		this->listaTekstur[i].textureHeight = height;
	}


	std::vector<unsigned char> imageTab;
	for(int i=number-1;i>=0;i--)
		for(int j=0; j < (int)this->listaTekstur[i].image.size();j++)
			imageTab.push_back(this->listaTekstur[i].image[j]);

   glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,this->listaTekstur[0].textureWidth,this->listaTekstur[0].textureHeight,number, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageTab.data());

	// glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,this->listaTekstur[0].textureWidth,this->listaTekstur[0].textureHeight,number, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) imageTab.data());
	// glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,this->listaTekstur[0].textureWidth,this->listaTekstur[0].textureHeight,number, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	// this->listaTekstur[0].image.data());

	// glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,this->listaTekstur[0].textureWidth,this->listaTekstur[0].textureHeight,number, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	// imageTab.data());

	glGenerateMipmap(GL_TEXTURE_3D);

	// for(int i=0;i<number;i++)
	// delete imageTab[i];
	// delete imageTab;
}

void Object::bindBuffers(int stride, GLenum usage) {
	this->initBinding();
	this->bufferData(usage);

	this->inBinding();

	this->vAttributePointer(3, stride);
	this->endBinding();
}

void Object::bufferData(GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), usage);
}

void Object::vAttributePointer(int firstVertex, int stride) {
	glVertexAttribPointer(0, firstVertex, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	int nextVertex = stride - firstVertex;
	if(nextVertex > 0){
		glVertexAttribPointer(1, nextVertex, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(firstVertex * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
}

//
//void Object::draw(int points) {
//	this->shader->useShaderProgram(0);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, this->texture2D);
//
//	glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
//	GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
//	glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->sclM*this->rotM));
//
//	glBindVertexArray(this->currentVAO());
//	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}

void Object::draw(){

}

GLint Object::getUniform(const char *nazwa) {
	return glGetUniformLocation(this->shader->shaderProgram[this->currentShader],nazwa);
}
