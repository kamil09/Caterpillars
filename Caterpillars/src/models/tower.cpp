#include "tower.hpp"

TowerLight* TowerLight::parent = nullptr;
Tower* Tower::parent = nullptr;

void TowerLight::moveLight(){
   this->direction == 0 ? this->rot.y+=0.005 : this->rot.y -=0.005;
   if (this->rot.y > this->endA) this->direction=1;
   if (this->rot.y < this->startA) this->direction=0;
   this->recalculateMatrix();
   this->lightDir = glm::vec4(0.0f,-1.0f,-1.0f,1.0f);
   lightDir = this->rotM*lightDir;
}

TowerLight::TowerLight(char*filename,Object *o, float startA, float endA, int dir){
//   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   if(this->parent== nullptr){
      this->parent = new TowerLight(filename);
   }
   this->scl=glm::vec3(8,8,8);
   this->pos=o->pos;
   this->pos.y+=(14.6*o->scl.y);

   this->rot.x=0;
   this->rot.z=0;
   this->rot.y=startA*2*3.14f/360;

   this->startA=startA*2*3.14f/360;
   this->endA=endA*2*3.14f/360;

   this->direction=dir;

   this->recalculateMatrix();
   this->copyParent();
//   loadObj::load(filename,&this->vertices, &this->indices);
//   this->bindBuffers(5,8,GL_STATIC_DRAW);
//   this->bindTexture2D("../src/img/towerL.png");
//   this->bindLightMap2D("../src/img/light/example.png");
//   this->bindShadwMap2D("../src/img/towerL.png");
}


void TowerLight::copyParent() {
   this->shader = this->parent->shader;
   this->currentShader = this->parent->currentShader;
//   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->vertices = this->parent->vertices;
   this->indices = this->parent->indices;
//   loadObj::load(filename,&this->vertices, &this->indices);
   this->buffers = this->parent->buffers;
   this->currentBinding = this->parent->currentBinding;
//   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->texture2D = this->parent->texture2D;
//   this->bindTexture2D("../src/img/towerL.png");
   this->lightMap = this->parent->lightMap;

//   this->bindLightMap2D("../src/img/light/example.png");
   this->shadowMap = this->parent->shadowMap;

//   this->bindShadwMap2D("../src/img/towerL.png");

}


TowerLight::TowerLight(char *filename) {
   std::cout << "###TWORZENIE TOWERLIGHT###" << std::endl;
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/towerL.png");
   this->bindLightMap2D("../src/img/light/towerLLight.png");
   this->bindShadwMap2D("../src/img/towerL.png");
}


TowerLight::~TowerLight(){};

void TowerLight::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->modM=this->posM * this->sclM * this->rotM;
   Object::draw(projection,modelView,lights,sun);
}

Tower::Tower(char *filename, int posX, int posY, int posZ, int startAngle, int endAngle){
//   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   if(this->parent == nullptr){
      this->parent = new Tower(filename);
   }
   this->size=glm::vec3(40,100,40);
   this->scl=glm::vec3(10,10,10);
   this->pos=glm::vec3(posX,posY,posZ);

   this->recalculateMatrix();

//   loadObj::load(filename,&this->vertices, &this->indices);
//   this->bindBuffers(5,8,GL_STATIC_DRAW);
//   this->bindTexture2D("../src/img/tower.png");
//   this->bindLightMap2D("../src/img/light/example.png");
//   this->bindShadwMap2D("../src/img/tower.png");
   this->copyParent();
   this->light = new TowerLight((char*)"../src/obj/towerL.obj",this,(float)startAngle,(float)endAngle,0);
}


void Tower::copyParent() {
   this->shader = this->parent->shader;
   this->currentShader = this->parent->currentShader;
//   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->vertices = this->parent->vertices;
   this->indices = this->parent->indices;
//   loadObj::load(filename,&this->vertices, &this->indices);
   this->buffers = this->parent->buffers;
   this->currentBinding = this->parent->currentBinding;
//   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->texture2D = this->parent->texture2D;
//   this->bindTexture2D("../src/img/tower.png");
   this->lightMap = this->parent->lightMap;

//   this->bindLightMap2D("../src/img/light/example.png");
   this->shadowMap = this->parent->shadowMap;

//   this->bindShadwMap2D("../src/img/tower.png");

}


Tower::Tower(char *filename) {
   std::cout << "###TWORZENIE TOWER###" << std::endl;
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");

   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/tower.png");
   this->bindLightMap2D("../src/img/light/towerLight.png");
   this->bindShadwMap2D("../src/img/tower.png");
}


Tower::~Tower(){}

void Tower::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
  this->modM=this->posM * this->sclM;
  Object::draw(projection,modelView,lights,sun);
  this->light->draw(projection,modelView,lights,sun);
}
