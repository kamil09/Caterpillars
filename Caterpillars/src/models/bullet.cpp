#include "bullet.hpp"

Bullet::Bullet(char *filename, float randDam){
   //wartosci wylosowana Damage
   this->damage = randDam;


   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");
   this->scl.x=4;
   this->scl.y=4;
   this->scl.z=4;
   this->recalculateMatrix();

  loadObj::load(filename,&this->vertices, &this->indices);
  this->bindBuffers(5,8,GL_STATIC_DRAW);
  this->bindTexture2D("../src/img/bullet.png");
  this->bindLightMap2D("../src/img/light/example.png");
  this->bindShadwMap2D("../src/img/shadow/example.png");

  this->size.y=0;//2
  this->size.x=2;//2
  this->size.z=1;//1
  this->used=false;
}
Bullet::~Bullet(){

}
void Bullet::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}

void Bullet::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
  this->shader->useShaderProgram(0);
  this->uniformTextures();

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
   GLint L = glGetUniformLocation(this->shader->shaderProgram[0], "L");
   GLint SUN = glGetUniformLocation(this->shader->shaderProgram[0], "SUN");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->rotMY*this->sclM));
   glUniformMatrix4fv(L, 1, GL_FALSE, glm::value_ptr(lights));
   glUniform4fv(SUN, 1, glm::value_ptr(sun));

   glBindVertexArray(this->currentVAO());
	   glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
   glBindVertexArray(0);
}
