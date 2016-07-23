#include "object.hpp"
#include "state/game/map/map.hpp"
#include "state/game/game.hpp"
#include "inputActions.hpp"

Object::Object(){
	this->teksturCount = 0;
	this->colission = false;//dla bulleta

	this->currentBinding = 0;
	this->buffersCount = 0;
	this->verticesCount = 0;
	this->indicesCount = 0;
	this->czyNormalMap = 0;
	this->windMul=0;
	this->speed.x=0;
	this->speed.y=0;
	this->speed.z=0;
	this->kickTime=0;
	this->canKick=true;
	this->size = glm::vec3(1.0f);
	this->normalMap = 0;
}

Object::~Object(){}

void Object::uniformTextures(){
	glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
	if(this->shadowMap!=0)glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "shadowMap"), 1);
	if(this->lightMap!=0)glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "lightMap"), 2);
	if(this->normalMap!=0)glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "normalMap"), 3);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
	if(this->shadowMap!=0){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->shadowMap);
	}
	if(this->lightMap!=0){
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, this->lightMap);
	}
	if(this->normalMap!=0){
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, this->normalMap);
	}
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
//        this->rotMY =  glm::rotate(glm::mat4(1),-this->rot.y,glm::vec3(0.0f,1.0f,0.0f));
//    this->rotM = glm::mat4(1);
//    this->rotM = glm::rotate(this->rotM,-this->rot.y,glm::vec3(0.0f,1.0f,0.0f));
//    this->rotM = glm::rotate(this->rotM,-this->rot.x,glm::vec3(1.0f,0.0f,0.0f));
//    this->rotM = glm::rotate(this->rotM,-this->rot.z,glm::vec3(0.0f,0.0f,1.0f));
	this->rotM=this->rotMY*rotZ*rotX;
}

void Object::kick(float x,float y, float z){
	this->speed.x=x;
	this->speed.y=y;
	this->speed.z=z;
}
void Object::recalculatePhysics(){}

void Object::recalculateGravity(float timeDifference) {
	if(timeDifference !=0.0f){
		bet_time = inputActions::getInstance().deltaTime;
	}
	else{
		std::cout << "###ERROR:DZIELENIE PRZEZ 0 FUNKCJA recalculateGravity:ERROR###" << std::endl;
	}
	in_meter = 1;//ile jednostek mamy w pseudo metrze
	//jesli wejdzie drugi raz
	if(sec_time)
	{
		if(!Game::checkCollisionAndMove(this, this->pos.x, this->pos.y,this->pos.z,inputActions::getInstance().objectPointers))
		{
			//gdy mamy kolizje obiektu z mapa
			//cout << ""Mapa - kolizja" << endl;
			this->pos.y = Map::getInstance().mapVert[(int)this->pos.x][(int)this->pos.z] + this->size.y + 1;
			this->on_the_ground = true;
			if(!this->speed.x || !this->speed.y || !this->speed.z) // zerowanie predkosci po opadnieciu na mape
			{
				this->speed.x = 0;
				this->speed.y = 0;
				this->speed.z = 0;
			}
		}
		else if(Game::checkCollisionAndMove(this, this->pos.x, this->pos.y,
			 				this->pos.z, inputActions::getInstance().objectPointers))
		{
			if(!this->on_the_ground)
			{
				windX = bet_time * Map::getInstance().windForce.x * this->windMul;
				windY = bet_time * Map::getInstance().windForce.y * this->windMul;
				windZ = bet_time * Map::getInstance().windForce.z * this->windMul;
				//cout << windMul;
				//tutaj nalezy uwzglednic jeszcze sile wiatru
				this->speed.x +=  windX;//*windMul
				this->speed.z +=  windZ;//*windMul
			}
//			this->przyspeszenieY -=Map::getInstance().gravity * bet_time * in_meter/timeDifference;
			this->speed.y -= Map::getInstance().gravity * in_meter * bet_time/timeDifference -windY;
//			this->speed.y += this->przyspeszenieY -windY;

			//DO TESTOW;
			float speedX = this->speed.x * bet_time/timeDifference;
			float speedY = this->speed.y * bet_time/timeDifference;
			float speedZ = this->speed.z * bet_time/timeDifference;

			nextX = this->pos.x + speedX;
			nextY = this->pos.y + speedY;
			nextZ = this->pos.z + speedZ;

			if(!Game::checkCollisionAndMove(this, nextX, nextY, nextZ,inputActions::getInstance().objectPointers))
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

void Object::diagonalThrow(glm::vec3 throw_speed)
{
	this->on_the_ground = false;
	this->speed.x = throw_speed.x;
	this->speed.y = throw_speed.y;
	this->speed.z = throw_speed.z;
}

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
	this->buffersCount++;
	this->buffers.push_back(new Buffers());
	if(this->buffers.empty()) {
		std::cerr << "ERROR::EMPTY BUFFER::ERROR" << std::endl;
	}
	this->currentBinding = this->buffersCount-1;
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

void Object::bindTexture2D(const GLchar *texturePath, GLuint *handle){
	glGenTextures(1, handle);
	glBindTexture(GL_TEXTURE_2D, *handle);
	this->paramText2D();
	this->loadTexture2D(texturePath);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Object::loadTexture2D(const GLchar *texturePath){
	std::vector<unsigned char> image;
	unsigned width,height;
	unsigned error = lodepng::decode(image,width,height,texturePath);
	if(error != 0) {
		std::cout << "ERROR:: " << error << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	errorCheck("Po loadTexture");
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Object::bindTexture3D(int number, vector<std::string> texturePath){
	glGenTextures(1, &this->texture3D);
	glBindTexture(GL_TEXTURE_3D, this->texture3D); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	//Set our texture parameters
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	listaTekstur.resize(number);
	for( int i=0;i<number;i++ ) this->listaTekstur[i].texturePath = texturePath[i].c_str();

	this->loadTexture3D(number);
	glBindTexture(GL_TEXTURE_3D, 0);
	errorCheck("Po loadTexture");
}

void Object::loadTexture3D(int number){
	int i;
	this->teksturCount = number;
	for(i=0; i < number; i++) {
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
	glGenerateMipmap(GL_TEXTURE_3D);
}

void Object::bindBuffers(int stride, int stride2, GLenum usage) {
	this->initBinding();
	this->bufferData(usage);

	this->inBinding();

	this->vAttributePointer(3, stride, stride2);
	this->endBinding();
}

void Object::bufferData(GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), usage);
}

void Object::vAttributePointer(int firstVertex, int stride, int stride2) {
	glVertexAttribPointer(0, firstVertex, GL_FLOAT, GL_FALSE, stride2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	int nextVertex = stride - firstVertex;

	if(nextVertex > 0){
		glVertexAttribPointer(1, nextVertex, GL_FLOAT, GL_FALSE, stride2 * sizeof(GLfloat), (GLvoid*)(firstVertex * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	nextVertex = stride2-stride;
	if(nextVertex > 0){
		glVertexAttribPointer(2, nextVertex, GL_FLOAT, GL_FALSE, stride2 * sizeof(GLfloat), (GLvoid*)(stride * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
}

void Object::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}

void Object::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
	this->shader->useShaderProgram(0);
   this->uniformTextures();

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
   GLint L = glGetUniformLocation(this->shader->shaderProgram[0], "L");
	GLint N = glGetUniformLocation(this->shader->shaderProgram[0], "czyNormalMap");
   GLint SUN = glGetUniformLocation(this->shader->shaderProgram[0], "SUN");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->modM));
   glUniformMatrix4fv(L, 1, GL_FALSE, glm::value_ptr(lights));
	glUniform1i(N, this->czyNormalMap);
   glUniform4fv(SUN, 1, glm::value_ptr(sun));

   glBindVertexArray(this->currentVAO());
   glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glBindVertexArray(0);
}

GLint Object::getUniform(const char *nazwa) {
	return glGetUniformLocation(this->shader->shaderProgram[this->currentShader],nazwa);
}


void Object::bindTextureCube(std::vector<std::string> faces, GLuint *handle) {
	glGenTextures(1, handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *handle);
	this->loadTextureCube(faces);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}


void Object::loadTextureCube(std::vector<std::string> faces) {
	std::cout << "Faces size: " << faces.size() << std::endl;
	for (int i = 0; i < faces.size(); ++i) {
		std::cout << faces[i] << std::endl;
		std::vector<unsigned char> image;
		unsigned width,height;
		unsigned error = lodepng::decode(image,width,height, faces[i].c_str());
		if(error != 0) {
			std::cout << "ERROR:: " << error << std::endl;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	}
	errorCheck("Po loadCube");
}

