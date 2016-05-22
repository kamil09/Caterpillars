#include "object2D.hpp"


object2D::object2D(float x, float y, float width, float height, GLchar *fileName){
   this->shader = new Shader("../src/shaders/2dTex.vs","../src/shaders/2dTex.frag");
   this->vertices.resize(4);
   this->indices.resize(4);
   this->vertices = {
      x, y, 0.0f, 0.0f, 0.0f,
      x+width, y,  0.0f, 1.0f, 0.0f,
      x, y+height, 0.0f, 0.0f, 1.0f,
      x+width, y+height, 0.0f, 1.0f, 1.0f,
   };
   this->indices = {
      0,1,2,3
   };
   this->bindBuffers();
   this->bindTexture2D(fileName);
   this->posM = glm::mat4(1);
   this->rotM = glm::mat4(1);
   this->sclM = glm::mat4(1);
   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport);
   this->sclM[0][0]=1.0f/viewport[2];
   this->sclM[1][1]=1.0f/viewport[3];
}
void object2D::setTraM(float x,float y,float z){
   this->posM[3][0]=x;
   this->posM[3][1]=y;
   this->posM[3][2]=z;
}
object2D::~object2D(){

}

void object2D::bindBuffers(){
   this->initBinding(true);

   glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(1);

   this->endBinding();
}
void object2D::draw(){
   this->shader->useShaderProgram(0);
   glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);

   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->sclM*this->rotM));

   glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
}
