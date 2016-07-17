#include "gun.hpp"

Gun::Gun(char *filename, int min, int max,Object *owner){
   //wartosci pomiedzy ktorymi bedziemy losowac Damage podczas strzelu
   this->minDamage = min;
   this->maxDamage = max;
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->scl=owner->scl;

   this->posMadd=glm::mat4(1);
   this->posMadd[3][0]=owner->size.x;
	this->posMadd[3][2]=owner->size.z*2.5;
   this->posMadd[3][1]=owner->size.y*3;
   this->recalculateMatrix();

   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/weapon.png");
   this->bindLightMap2D("../src/img/light/example.png");
   this->bindShadwMap2D("../src/img/weapon.png");
   puts("create weapon");
}
Gun::~Gun(){}

void Gun::draw(glm::mat4 projection, glm::mat4 modelView, Object *owner, glm::mat4 lights,glm::vec4 sun){
  this->modM=(owner->posM) *(owner->rotMY)* this->posMadd* (owner->sclM);
  Object::draw(projection,modelView,lights,sun) ;
}
