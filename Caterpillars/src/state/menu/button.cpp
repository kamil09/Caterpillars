#include "button.hpp"

Button::Button(int index, float x, float y, float width, float height, GLchar *fileName,
               std::function<void(GLFWwindow *, GLFWcursor *)> callBack) : object2D(x, y, width, height,
                                                                                    fileName) {
    this->shader = new Shader("../src/shaders/button/buttonShaderTexture.vs","../src/shaders/button/buttonShaderTexture.frag");
    this->callBackFunction = callBack;
    this->check = 0;
    int red = ((index & 0x000000FF) >>  0);
    int green = ((index & 0x0000FF00) >>  8);
    int blue = ((index & 0x00FF0000) >> 16);
    this->r = red/255.0f;
    this->g = green/255.0f;
    this->b = blue/255.0f;
}

Button::~Button(){
	std::cout << "usuwanie buttona" << std::endl;
	// glDeleteVertexArrays(1, &this->VAO);
	// glDeleteBuffers(1, &this->VBO);
	// glDeleteBuffers(1, &this->EBO);
}

//void Button::draw(int check){
//errorCheck("Przed draw2");
//	this->shader->useShaderProgram(0);
//	errorCheck("Po draw2");
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, this->texture2D);
//    glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
//
////	GLint uniformLocation = glGetUniformLocation(this->shader->shaderProgram[0], "positionZ"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
////	if(check!=0){
////		if(this->r > 0.0f || this->g > 0.0f || this->b > 0.0f){
////			// std::cout << "button" << std::endl;
////			glUniform1f(uniformLocation, -0.6f);
////		}
////		else{
////			// std::cout << "background" << std::endl;
////			glUniform1f(uniformLocation, -0.5f);
////		}
////	}
////	else{
////		glUniform1f(uniformLocation, this->pos.z);
////	}
////	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
////	glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
////
////	GLint uniformLocation2 = glGetUniformLocation(this->shader->shaderProgram[0], "check"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
////	glUniform1i(uniformLocation2,check);
//
//
//	glBindVertexArray(this->currentVAO());
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}

void Button::inUniform() {
    errorCheck("Uniform");
	GLint uniformLocation = glGetUniformLocation(this->shader->shaderProgram[0], "positionZ"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	if(this->check!=0){
		glUniform4f(vertexColorLocation,1.0f, 1.0f, 1.0f, this->alpha);
		if(this->r > 0.0f || this->g > 0.0f || this->b > 0.0f){
			// std::cout << "button" << std::endl;
			this->pos.z=0.6f;
			// 	glUniform1f(uniformLocation, +0.6f);
		}
		else{
//			glUniform4f(vertexColorLocation,1.0f, 1.0f, 1.0f, 1.0f);
			this->pos.z=0.5f;
			// std::cout << "background" << std::endl;
//			glUniform1f(uniformLocation, +0.5f);
		}
	}
	else{
		glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
		this->pos.z = 0.0f;
//		glUniform1f(uniformLocation, this->pos.z);
	}
	glUniform1f(uniformLocation, this->pos.z);
//	if(this->check!=0){
//		glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
//	}
//	else{
//
//	}

	GLint uniformLocation2 = glGetUniformLocation(this->shader->shaderProgram[0], "check");
	glUniform1i(uniformLocation2,this->check);

}