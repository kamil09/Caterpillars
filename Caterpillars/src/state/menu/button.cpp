#include "button.hpp"

// Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight,std::string texturePath){
Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath){
	this->shader = new Shader("../src/shaders/button/buttonShader.vs","../src/shaders/button/buttonShader.frag");
	// this->shader->loadShader("../src/shaders/buttonShader.vs", "../src/shaders/buttonShader.frag");

	int red = ((i & 0x000000FF) >>  0);
	int green = ((i & 0x0000FF00) >>  8);
	int blue = ((i & 0x00FF0000) >> 16);
	this->r = red/255.0f;
	this->g = green/255.0f;
	this->b = blue/255.0f;

	std::cout << "Kolory: r = " << this->r << " g = " << this->g << " b = " << this->b << std::endl;
	this->posX = newX;
   this->posY = newY;
	this->posZ = newZ;

    this->width = newWidth;
    this->height = newHeight;

	this->vertices.resize(20);
	this->vertices[0] = this->posX + this->width/2.0f;
	this->vertices[1] = this->posY + this->height/2.0f;
	this->vertices[2] = this->posZ;
	this->vertices[3] = 1.0f;
	this->vertices[4] = 1.0f;

	this->vertices[5] = this->posX + this->width/2.0f;
	this->vertices[6] = this->posY - this->height/2.0f;
	this->vertices[7] = this->posZ;
	this->vertices[8] = 1.0f;
	this->vertices[9] = 0.0f;

	this->vertices[10] = this->posX - this->width/2.0f;
	this->vertices[11] = this->posY - this->height/2.0f;
	this->vertices[12] = this->posZ;
	this->vertices[13] = 0.0f;
	this->vertices[14] = 0.0f;

	this->vertices[15] = this->posX - this->width/2.0f;
	this->vertices[16] = this->posY + this->height/2.0f;
	this->vertices[17] = this->posZ;
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

	this->bindBuffers();
	this->bindBuffers2();

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


void Button::bindBuffers(){
	this->initBinding(true);
	//Od tego momentu zmieniamy!
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	this->endBinding();
	// glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//
	// glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void Button::bindBuffers2(){
	this->shader->loadShader("../src/shaders/button/buttonShaderTexture.vs", "../src/shaders/button/buttonShaderTexture.frag");
	this->initBinding(true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   	glEnableVertexAttribArray(1);
	this->endBinding();
}

void Button::draw(){
	// std::cout << "hej" << std::endl;
	// glUseProgram(this->shader->);
	this->currentBinding = 0;
	this->shader->useShaderProgram(0);
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    // glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
	// std::cout << "kolory: r = " << this->r << " g = " << this->g << " b = " << this->b << std::endl;
	glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
    glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Button::draw2(){
	this->currentBinding = 1;
	errorCheck("Przed draw2");
	this->shader->useShaderProgram(1);
	errorCheck("Po draw2");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
    glUniform1i(glGetUniformLocation(this->shader->shaderProgram[1], "ourTexture1"), 0);
	GLint uniformLocation = glGetUniformLocation(this->shader->shaderProgram[1], "positionZ"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	if(this->r > 0 || this->g > 0.0f || this->b > 0.0f){
		// std::cout << "button" << std::endl;
		glUniform1f(uniformLocation, -1.0f);
	}
	else{
		// std::cout << "background" << std::endl;
		glUniform1f(uniformLocation, -0.5f);
	}

	// GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram, "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    // glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
    glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Button::select(){
	std::cout << "wybrano przycisk o kolorze red: " << this->r << " green: " << this->g << " blue: " << this->b << std::endl;
}
