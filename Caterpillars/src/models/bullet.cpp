#include "bullet.hpp"

Bullet* Bullet::parent = nullptr;

Bullet::Bullet(char *filename, float shotPower){
   if(this->parent== nullptr){
      this->parent = new Bullet(filename);
   }
   //wartosci wylosowana Damage
   this->shotPower = shotPower;
   this->copyParent();
}


Bullet::Bullet(char *filename) {
   std::cout << "###TWORZENIE BULLETU###" << std::endl;
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->scl=glm::vec3(4,4,4);
   this->recalculateMatrix();
   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/bullet.png",&this->texture2D);
   this->bindTexture2D("../src/img/light/bulletLight.png",&this->lightMap);
   this->bindTexture2D("../src/img/shadow/bulletShadow.png",&this->shadowMap);
   this->size=glm::vec3(0,2,1);
   this->used=false;
}


void Bullet::copyParent() {
   this->shader = this->parent->shader;
   this->currentShader = this->parent->currentShader;
//   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->scl=this->parent->scl;
//   this->scl=glm::vec3(4,4,4);
   this->recalculateMatrix();
   this->vertices = this->parent->vertices;
   this->indices = this->parent->indices;
//   loadObj::load(filename,&this->vertices, &this->indices);
   this->buffers = this->parent->buffers;
   this->currentBinding = this->parent->currentBinding;
//   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->texture2D = this->parent->texture2D;
//   this->bindTexture2D("../src/img/bullet.png");
   this->lightMap = this->parent->lightMap;
//   this->bindLightMap2D("../src/img/light/example.png");
   this->shadowMap = this->parent->shadowMap;
//   this->bindShadwMap2D("../src/img/bullet.png");
   this->size=this->parent->size;
//   this->size=glm::vec3(0,2,1);
   this->used=this->parent->used;
//   this->used=false;

}


Bullet::~Bullet(){}

void Bullet::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
//   this->modM=this->posM*this->rotM*this->sclM;
   this->modM=this->posM*this->rotM*this->sclM;
   Object::draw(projection,modelView,lights,sun);
}


void Bullet::recalculateRotZ() {
   float rotz;
   float wynikDzielenia = this->speed.y/this->shotPower;
   if(wynikDzielenia > 1.0f){
      rotz = glm::radians(85.0f);
//      wynikDzielenia = 1.0f;
   }
   else if(wynikDzielenia < -1.0f){
      rotz = glm::radians(-85.0f);
//      wynikDzielenia = -1.0f;
   }
   else{
      rotz = asin(wynikDzielenia);
   }
   if(rotz != rotz){
      std::cout << "BLAD" << std::endl;
   }
//   if(glm::degrees(rotz) > 90.0f){
//      rotz = glm::radians(90.0f);
//   }
   this->rot.z = -rotz;
}
