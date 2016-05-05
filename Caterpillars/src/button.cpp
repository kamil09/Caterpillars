#include "button.hpp"

Button::Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight){
	this->shader = new Shader("../src/shader.vs","../src/shader.frag");

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

	this->vertices.resize(12);
	this->vertices[0] = this->getPosX() + this->width/2.0f;
	this->vertices[1] = this->getPosY() + this->height/2.0f;
	this->vertices[2] = 0.0f;
	this->vertices[3] = this->getPosX() + this->width/2.0f;
	this->vertices[4] = this->getPosY() - this->height/2.0f;
	this->vertices[5] = 0.0f;
	this->vertices[6] = this->getPosX() - this->width/2.0f;
	this->vertices[7] = this->getPosY() - this->height/2.0f;
	this->vertices[8] = 0.0f;
	this->vertices[9] = this->getPosX() - this->width/2.0f;
	this->vertices[10] = this->getPosY() + this->height/2.0f;
	this->vertices[11] = 0.0f;

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
	this->bindBuffers();
}

Button::~Button(){
	std::cout << "usuwanie buttona" << std::endl;
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}


void Button::bindBuffers(){
	std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	glDisableVertexAttribArray(0);
}

void Button::rysuj(){
	glUseProgram(this->shader->shaderProgram);
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram, "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    glUniform4f(vertexColorLocation, this->r/255.0f, this->g/255.0f, this->b/255.0f, 1.0f);
    glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Button::wybrano(){
	std::cout << "wybrano przycisk o kolorze red: " << this->r/255.0f << " green: " << this->g/255.0f << " blue: " << this->b/255.0f << std::endl;

}
