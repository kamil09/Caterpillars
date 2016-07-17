#include "tower.hpp"

void TowerLight::moveLight(){
   this->direction == 0 ? this->rot.y+=0.005 : this->rot.y -=0.005;
   if (this->rot.y > this->endA) this->direction=1;
   if (this->rot.y < this->startA) this->direction=0;
   this->recalculateMatrix();
   this->lightDir = glm::vec4(0.0f,-1.0f,-1.0f,1.0f);
   lightDir = this->rotM*lightDir;
}

TowerLight::TowerLight(char*filename,Object *o, float startA, float endA, int dir){
   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");

   this->scl.x=8;
   this->scl.y=8;
   this->scl.z=8;

   this->pos.x=o->pos.x;
   this->pos.y=o->pos.y;
   this->pos.z=o->pos.z;
   this->pos.y+=(14.8*o->scl.y);

   this->rot.x=0;
   this->rot.z=0;
   this->rot.y=startA*2*3.14/360;

   this->startA=startA*2*3.14/360;
   this->endA=endA*2*3.14/360;

   this->direction=dir;

   this->recalculateMatrix();

   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/towerL.png");
   this->bindLightMap2D("../src/img/light/example.png");
   this->bindShadwMap2D("../src/img/shadow/example.png");
   puts("created tower light");

}

TowerLight::~TowerLight(){};

void TowerLight::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->modM=this->posM * this->sclM * this->rotM;
   Object::draw(projection,modelView,lights,sun);
}

Tower::Tower(char *filename, int posX, int posY, int posZ, int startAngle, int endAngle){
   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");

   this->size.x = 40;
   this->size.y = 100; //Tu nie wiem jaka wartosc
   this->size.z = 40;

   this->scl.x=10;
   this->scl.y=10;
   this->scl.z=10;

   this->pos.x=posX;
   this->pos.y=posY;
   this->pos.z=posZ;

   this->recalculateMatrix();

   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/tower.png");
   this->bindLightMap2D("../src/img/light/example.png");
   this->bindShadwMap2D("../src/img/shadow/example.png");
   puts("created tower");

   this->light = new TowerLight((char*)"../src/obj/towerL.obj",this,(float)startAngle,(float)endAngle,0);
}

Tower::~Tower(){}

void Tower::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
  this->modM=this->posM * this->sclM;
  Object::draw(projection,modelView,lights,sun);
  this->light->draw(projection,modelView,lights,sun);
}
