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

Bullet::~Bullet(){}

void Bullet::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->modM=this->posM*this->rotMY*this->sclM;
   Object::draw(projection,modelView,lights,sun);
}
