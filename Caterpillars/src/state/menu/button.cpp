#include "button.hpp"

// Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath){
// Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath,void(*callBack)(void)){
Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath,std::function<void(GLFWwindow* ,GLFWcursor*)> callBack){
	this->callBackFunction = callBack;
//	this->shader = new Shader("../src/shaders/button/buttonShader.vs","../src/shaders/button/buttonShader.frag");
	this->shader = new Shader("../src/shaders/button/buttonShaderTexture.vs","../src/shaders/button/buttonShaderTexture.frag");
//	this->shader->loadShader("../src/shaders/button/buttonShaderTexture.vs", "../src/shaders/button/buttonShaderTexture.frag");

	// this->shader->loadShader("../src/shaders/buttonShader.vs", "../src/shaders/buttonShader.frag");

	int red = ((i & 0x000000FF) >>  0);
	int green = ((i & 0x0000FF00) >>  8);
	int blue = ((i & 0x00FF0000) >> 16);
	this->r = red/255.0f;
	this->g = green/255.0f;
	this->b = blue/255.0f;

	std::cout << "Kolory: r = " << this->r << " g = " << this->g << " b = " << this->b << std::endl;
	this->pos.x = newX;
   this->pos.y = newY;
	this->pos.z = newZ;

    this->width = newWidth;
    this->height = newHeight;

	this->vertices.resize(20);
	this->vertices[0] = this->pos.x + this->width/2.0f;
	this->vertices[1] = this->pos.y + this->height/2.0f;
	this->vertices[2] = this->pos.z;
	this->vertices[3] = 1.0f;
	this->vertices[4] = 1.0f;

	this->vertices[5] = this->pos.x + this->width/2.0f;
	this->vertices[6] = this->pos.y - this->height/2.0f;
	this->vertices[7] = this->pos.z;
	this->vertices[8] = 1.0f;
	this->vertices[9] = 0.0f;

	this->vertices[10] = this->pos.x - this->width/2.0f;
	this->vertices[11] = this->pos.y - this->height/2.0f;
	this->vertices[12] = this->pos.z;
	this->vertices[13] = 0.0f;
	this->vertices[14] = 0.0f;

	this->vertices[15] = this->pos.x - this->width/2.0f;
	this->vertices[16] = this->pos.y + this->height/2.0f;
	this->vertices[17] = this->pos.z;
	this->vertices[18] = 0.0f;
	this->vertices[19] = 1.0f;

	// this->vertices[] = {
	//      0.5f,  0.5f, 0.0f,  // Top Right
	//      0.5f, -0.5f, 0.0f,  // Bottom Right
	//     -0.5f, -0.5f, 0.0f,  // Bottom Left
	//     -0.5f,  0.5f, 0.0f   // Top Left
	// };

	this->indices.resize(6);
	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 3;
	this->indices[3] = 1;
	this->indices[4] = 2;
	this->indices[5] = 3;

	//
	//     0, 1, 3,  // First Triangle
	// this->indices[] = {  // Note that we start from 0!
	//     1, 2, 3   // Second Triangle
	// };
	errorCheck("Przed bindTexture");
	this->bindBuffers(5,GL_STATIC_DRAW);
//	this->bindBuffers();
//	this->bindBuffers2();

	// std::cout << "texture path: " << texturePath << std::endl;
	this->bindTexture2D(texturePath);
	// this->bindTexture2D(texturePath.c_str());
	std::cout << "Koniec tworzenia buttona" << std::endl;
}

Button::~Button(){
	std::cout << "usuwanie buttona" << std::endl;
	// glDeleteVertexArrays(1, &this->VAO);
	// glDeleteBuffers(1, &this->VBO);
	// glDeleteBuffers(1, &this->EBO);
}


//void Button::bindBuffers(){
//	this->initBinding(true);
//	//Od tego momentu zmieniamy!
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	this->endBinding();
//	// glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
//	//
//	// glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
//
//}
//
//void Button::bindBuffers2(){
//	this->initBinding(true);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//   	glEnableVertexAttribArray(1);
//	this->endBinding();
//}

//void Button::draw(){
//	// std::cout << "hej" << std::endl;
//	// glUseProgram(this->shader->);
//	this->currentBinding = 0;
//	this->shader->useShaderProgram(0);
//	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
//    // glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
//	// std::cout << "kolory: r = " << this->r << " g = " << this->g << " b = " << this->b << std::endl;
//	glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
//    glBindVertexArray(this->currentVAO());
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//}

void Button::draw(int check){
//	this->currentBinding = 1;
	errorCheck("Przed draw2");
	this->shader->useShaderProgram(0);
	errorCheck("Po draw2");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
    glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
	GLint uniformLocation = glGetUniformLocation(this->shader->shaderProgram[0], "positionZ"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	if(check!=0){

		if(this->r > 0.0f || this->g > 0.0f || this->b > 0.0f){
			// std::cout << "button" << std::endl;
			glUniform1f(uniformLocation, -0.6f);
		}
		else{
			// std::cout << "background" << std::endl;
			glUniform1f(uniformLocation, -0.5f);
		}
	}
	else{
		glUniform1f(uniformLocation, this->pos.z);
	}
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);

	GLint uniformLocation2 = glGetUniformLocation(this->shader->shaderProgram[0], "check"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
//	if(check != 0){
//		std::cout << 1 << std::endl;
//		glUniform1i(uniformLocation2,1);
//	}
//	else{
//		std::cout << 0 << std::endl;
//		glUniform1i(uniformLocation2,0);
//	}
	glUniform1i(uniformLocation2,check);


	glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

// void Button::select(){
// 	std::cout << "wybrano przycisk o kolorze red: " << this->r << " green: " << this->g << " blue: " << this->b << std::endl;
// }
