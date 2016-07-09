#include "button.hpp"

Button::Button(int index, float x, float y, float width, float height, string fileName,
               std::function<void(Button *, GLFWwindow *, GLFWcursor *)> callBack) : object2D(x, y, width, height,
                                                                                    fileName) {
    this->shader = new Shader("../src/shaders/button/buttonShaderTexture.vs","../src/shaders/button/buttonShaderTexture.frag");
    this->callBackFunction = callBack;
    this->check = 0;
    int nowyIndex = index;
    int red = ((nowyIndex & 0x000000FF) >>  0);
    int green = ((nowyIndex & 0x0000FF00) >>  8);
    int blue = ((nowyIndex & 0x00FF0000) >> 16);
    this->kolor.r = red/255.0f;
    this->kolor.g = green/255.0f;
    this->kolor.b = blue/255.0f;
    this->kolor.a = 1.0f;
//    this->r = red/255.0f;
//    this->g = green/255.0f;
//    this->b = blue/255.0f;
    this->binds = -1;
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
//    glm::vec4 tempKolory;
    errorCheck("Uniform");
	GLint uniformLocation = glGetUniformLocation(this->shader->shaderProgram[0], "positionZ"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "uColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
    if(this->texture2D==NULL && this->check!=0){
        this->check = 0;
//        tempKolory = this->kolor2;
    }
//    else{
//        tempKolory = this->kolor;
//    }
//	if(this->check!=0){
//		glUniform4f(vertexColorLocation,1.0f, 1.0f, 1.0f, this->alpha);
    if(this->check==0){
        GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
        glm::mat4 temp = this->posM;
        temp[3][2] = 0.0f;
        glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(temp*this->sclM*this->rotM));
    }

    if(this->kolor.r > 0.0f || this->kolor.g > 0.0f || this->kolor.b > 0.0f){
		if(this->check!=0){
//            glUniform4f(vertexColorLocation,this->alpha, this->alpha, this->alpha, this->alpha);
            glUniform4f(vertexColorLocation,this->kolor.a, this->kolor.a, this->kolor.a, this->kolor.a);
            this->pos.z=0.1f;
        }
        else{
//            glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
            glUniform4f(vertexColorLocation, this->kolor.r, this->kolor.g, this->kolor.b, 0.0f);
            this->pos.z=-0.9f;
        }

		// std::cout << "button" << std::endl;
//			this->pos.z=-0.1f;
			// 	glUniform1f(uniformLocation, +0.6f);
	}
	else{
        if(this->check!=0){
//            glUniform4f(vertexColorLocation,this->alpha, this->alpha, this->alpha, this->alpha);
            glUniform4f(vertexColorLocation,this->kolor.a, this->kolor.a, this->kolor.a, this->kolor.a);
            this->pos.z=-0.1f;
        }
        else{
            glUniform4f(vertexColorLocation, this->kolor.r, this->kolor.g, this->kolor.b, 0.0f);
            this->pos.z=-1.0f;
        }

//			this->pos.z=0.5f;
//			this->pos.z=-0.2f;
        // std::cout << "background" << std::endl;
//			glUniform1f(uniformLocation, +0.5f);
    }
//			glUniform4f(vertexColorLocation,1.0f, 1.0f, 1.0f, 1.0f);
//	}
//	else{
//		glUniform4f(vertexColorLocation, this->r, this->g, this->b, 0.0f);
//		this->pos.z = 0.0f;
////		glUniform1f(uniformLocation, this->pos.z);
//	}
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


void Button::drawText() {
    if(this->check!=0){
        object2D::drawText();
    }
}

