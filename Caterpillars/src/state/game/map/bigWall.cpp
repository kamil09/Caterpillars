#include "bigWall.hpp"
#include "../../../inputActions.hpp"


Wall::Wall(int x, int width, int z, int depth, int min, int max){
   this->shader = new Shader("../src/shaders/map/wallShader.vs","../src/shaders/map/wallShader.frag");
   this->vertices.resize(8*3);
   this->indices.resize(10);
   this->vertices = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, (float)max,  0.0f, 0.0f, 1.0f,
      (float)width, 0.0f, 0.0f, 1.0f, 0.0f,
      (float)width, (float)max, 0.0f, 1.0f, 1.0f,
      (float)width, 0.0f, float(depth), 0.0f, 0.0f,
      (float)width, (float)max, float(depth), 0.0f, 1.0f,
      0.0f, 0.0f, float(depth), 1.0f, 0.0f,
      0.0f, (float)max, float(depth), 1.0f, 1.0f
   };
   this->indices = {
      0,1,2,3,4,5,6,7,0,1
   };
//   this->bindBuffers(true);
   this->bindBuffers(5,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/wall.png");
}

Wall::~Wall(){

}

//void Wall::bindBuffers(bool newBuffer){
//   this->initBinding(newBuffer);
//
//   glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//   glEnableVertexAttribArray(1);
//
//   this->endBinding();
//}
void Wall::draw(glm::mat4 projection, glm::mat4 modelView){
   this->shader->useShaderProgram(0);
   glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"),1);

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));

   glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);
   glBindVertexArray(1);
}
