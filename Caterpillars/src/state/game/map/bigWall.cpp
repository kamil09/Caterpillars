#include "bigWall.hpp"
#include "../../../inputActions.hpp"

Wall::Wall(char *filename, int x, int width, int z, int depth, int min, int max){
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->size.x = width;
   this->size.y = max; //Tu nie wiem jaka wartosc
   this->size.z = depth;
   this->scl.x=width/2;
   this->scl.y=max/2;
   this->scl.z=depth/2;
   this->pos.x=width/2;
   this->pos.y=max/2;
   this->pos.z=depth/2;
   this->recalculateMatrix();
   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/wall.png",&this->texture2D);
   this->bindTexture2D("../src/img/light/example.png",&this->lightMap);
   this->bindTexture2D("../src/img/shadow/example.png",&this->shadowMap);
   this->bindTexture2D("../src/img/normal/wallNormal.png",&this->normalMap);
   this->czyNormalMap=1;
}

Wall::~Wall(){}

void Wall::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->modM=this->posM*this->sclM;
   Object::draw(projection,modelView,lights,sun);
}
