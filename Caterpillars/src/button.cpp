#include "button.hpp"

Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight){
	this->shader = new Shader("../src/shaders/shader.vs","../src/shaders/shader.frag");

	this->r = ((i & 0x000000FF) >>  0);
	this->g = ((i & 0x0000FF00) >>  8);
	this->b = ((i & 0x00FF0000) >> 16);

	this->setPosX(newX);
    this->setPosY(newY);
    std::cout << "Pozycja X: " << this->getPosX() << " Pozycja Y:" << this->getPosY() << std::endl;


    this->width = newWidth;
    this->height = newHeight;

    std::cout << "Szerokosc: " << this->width << " Wysokosc:" << this->height << std::endl;

	std::cout << "Tworznenie buttonu" << std::endl;

	this->vertices.resize(20);
	this->vertices[0] = this->getPosX() + this->width/2.0f;
	this->vertices[1] = this->getPosY() + this->height/2.0f;
	this->vertices[2] = 0.0f;
	this->vertices[3] = 1.0f;
	this->vertices[4] = 1.0f;

	this->vertices[5] = this->getPosX() + this->width/2.0f;
	this->vertices[6] = this->getPosY() - this->height/2.0f;
	this->vertices[7] = 0.0f;
	this->vertices[8] = 1.0f;
	this->vertices[9] = 0.0f;

	this->vertices[10] = this->getPosX() - this->width/2.0f;
	this->vertices[11] = this->getPosY() - this->height/2.0f;
	this->vertices[12] = 0.0f;
	this->vertices[13] = 0.0f;
	this->vertices[14] = 0.0f;

	this->vertices[15] = this->getPosX() - this->width/2.0f;
	this->vertices[16] = this->getPosY() + this->height/2.0f;
	this->vertices[17] = 0.0f;
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
// this->indices[] = {  // Note that we start from 0!
	//     0, 1, 3,  // First Triangle
	//     1, 2, 3   // Second Triangle
	// };
	errorCheck("Przed bindTexture");

	this->bindBuffers();
	this->bindBuffers2();
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
	this->shader->loadShader("../src/shaders/buttonShader.vs", "../src/shaders/buttonShader.frag");
	this->initBinding(true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   	glEnableVertexAttribArray(1);
	this->endBinding();
	this->bindTexture2D("../src/img/menuLab1.png");
}

void Button::draw(){
	// glUseProgram(this->shader->);
	this->currentBinding = 0;
	this->shader->useShaderProgram(0);
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
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
	glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(glGetUniformLocation(this->shader->shaderProgram[1], "ourTexture1"), 0);
	// GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram, "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    // glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
    glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Button::select(){
	std::cout << "wybrano przycisk o kolorze red: " << this->r/255.0f << " green: " << this->g/255.0f << " blue: " << this->b/255.0f << std::endl;

}
