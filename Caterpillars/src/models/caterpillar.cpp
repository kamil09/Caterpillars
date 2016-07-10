#include "caterpillar.hpp"

Caterpillar::Caterpillar(char *filename){
   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");
   this->scl.x=3;
   this->scl.y=3;
   this->scl.z=3;
   this->recalculateMatrix();
   this->viewBack=0.0f;
   this->tmpViewBack=666.0f;

   this->windMul=0.1;
   this->life=100;
   this->maxWalkAngle=0.45;
   this->maxWalkSpeed=2;
   loadObj::load(filename,&this->vertices, &this->indices);
//   this->bindBuffers(true);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/catTX.png");
   this->startLook = glm::vec3(1.0f,0.0f,0.0f);

   this->weapon = new Gun( (char*)"../src/obj/weapon.obj",10,100,this);

   this->size.y=1.33;
   this->size.x=1.33;
   this->size.z=0.66;
}

Caterpillar::~Caterpillar(){}

void Caterpillar::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}

void Caterpillar::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec3 sun){
   this->shader->useShaderProgram(0);
   glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->texture2D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 3);

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
   GLint L = glGetUniformLocation(this->shader->shaderProgram[0], "L");
   GLint SUN = glGetUniformLocation(this->shader->shaderProgram[0], "SUN");


   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->rotMY*this->sclM));
   glUniformMatrix4fv(L, 1, GL_FALSE, glm::value_ptr(lights));
   glUniformMatrix4fv(SUN, 1, GL_FALSE, glm::value_ptr(sun));



   glBindVertexArray(this->currentVAO());
   glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
   glBindVertexArray(3);

   this->weapon->draw(projection,modelView,this,lights,sun);
}
