#include "bullet.hpp"

Bullet::Bullet(char *filename, float randDam){

    //wartosci wylosowana Damage
    this->Damage = randDam;

  //  this->shader = new Shader("../src/shaders/bulletShader.vs","../src/shaders/bulletShader.frag");
  //  this->scl.x=4;
  //  this->scl.y=4;
  //  this->scl.z=4;
  //  this->recalculateMatrix();
  //  this->viewBack=0.0f;
  //  this->tmpViewBack=666.0f;
   //
  //  loadObj::load(filename,&this->vertices, &this->indices);
  //  this->bindBuffers(5,GL_STATIC_DRAW);
  //  this->bindTexture2D("../src/img/gunTX.png");
  //  this->startLook = glm::vec3(1.0f,0.0f,0.0f);
   //
  //  this->size.y=2;
  //  this->size.x=2;
  //  this->size.z=1;
}
Bullet::~Bullet(){

}
void Bullet::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}

void Bullet::draw(glm::mat4 projection, glm::mat4 modelView){
  //  this->shader->useShaderProgram(0);
  //  glActiveTexture(GL_TEXTURE0);
	//  glBindTexture(GL_TEXTURE_2D, this->texture2D);
  //  glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
  //
  //  GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
  //  GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
  //  GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
  //
  //  glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
  //  glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
  //  glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->rotMY*this->sclM));
  //
  //  glBindVertexArray(this->currentVAO());
	// //glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  //  glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
  //  glBindVertexArray(0);
}
