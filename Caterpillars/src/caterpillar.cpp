#include "caterpillar.hpp"

Caterpillar::Caterpillar(char *filename){
   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");
   this->scl.x=4;
   this->scl.y=4;
   this->scl.z=4;
   this->recalculateMatrix();
   this->viewBack=0.0f;
   this->tmpViewBack=666.0f;

   this->windMul=0.1;
   this->life=100;
   this->maxWalkAngle=0.45;
   this->maxWalkSpeed=2;
   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(true);
   this->bindTexture2D("../src/img/catTX.png");
   this->startLook = glm::vec3(1.0f,0.0f,0.0f);

   this->size.y=2;
   this->size.x=2;
   this->size.z=1;
}
Caterpillar::~Caterpillar(){

}
void Caterpillar::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}
void Caterpillar::bindBuffers(bool newBuffer){
   this->initBinding(newBuffer);

   glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(1);

   this->endBinding();
}
void Caterpillar::draw(glm::mat4 projection, glm::mat4 modelView){
   this->shader->useShaderProgram(0);
   glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->rotMY*this->sclM));

   glBindVertexArray(this->currentVAO());
	//glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
   glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
   glBindVertexArray(0);
}
