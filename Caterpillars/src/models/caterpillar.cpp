#include <algorithm>
#include "caterpillar.hpp"


Caterpillar* Caterpillar::parent = nullptr;
Caterpillar* Caterpillar::box = nullptr;
Caterpillar::Caterpillar(char *filename, bool dead) {
   std::cout << "###TWORZENIE CATERPILLARA###" << std::endl;
   this->shader = new Shader("../src/shaders/basic3DShader.vs","../src/shaders/basic3DShader.frag");
   this->scl=glm::vec3(3,3,3);
   this->recalculateMatrix();
   this->viewBack=0.0f;
   this->tmpViewBack=666.0f;
   this->windMul=0.1;
   this->life=100;
   this->maxWalkAngle=0.45;
   this->maxWalkSpeed=5.0f;
    if(dead){
        this->dead=1;
        this->bindTexture2D("../src/img/box.png",&this->texture2D);
        this->bindTexture2D("../src/img/light/boxLight.png",&this->lightMap);
        this->bindTexture2D("../src/img/shadow/boxShadow.png",&this->shadowMap);

    }
    else{
        this->dead=0;
        this->bindTexture2D("../src/img/catTX.png",&this->texture2D);
        this->bindTexture2D("../src/img/light/catLight.png",&this->lightMap);
        this->bindTexture2D("../src/img/shadow/catTXShadow.png",&this->shadowMap);
    }
    loadObj::load(filename,&this->vertices, &this->indices);

   this->bindBuffers(5,8,GL_STATIC_DRAW);


   this->startLook = glm::vec3(1.0f,0.0f,0.0f);
   this->weapon = new Gun( (char*)"../src/obj/weapon.obj",10,100,this);
   this->size=glm::vec3(1.33,1.33,0.66);
}


Caterpillar::Caterpillar(Player *player, char *filename) {
    this->player = player;
    if(Caterpillar::parent== nullptr){
        Caterpillar::parent = new Caterpillar(filename, false);
    }
    if(Caterpillar::box== nullptr){
        Caterpillar::box = new Caterpillar((char*)"../src/obj/box.obj", true);
    }
    this->copyParent();
//    this->dead = 1;
}


void Caterpillar::copyParent() {
    this->shader = this->parent->shader;
    this->currentShader = this->parent->currentShader;
    this->scl.x=this->parent->scl.x;
    this->scl.y=this->parent->scl.y;
    this->scl.z=this->parent->scl.z;
//    this->scl.y=3;
//    this->scl.z=3;
    this->recalculateMatrix();
    this->viewBack=this->parent->viewBack;
    this->tmpViewBack=this->parent->tmpViewBack;
    this->dead = this->parent->dead;
    this->windMul=this->parent->windMul;
    this->life=this->parent->life;
    this->maxWalkAngle=this->parent->maxWalkAngle;
    this->maxWalkSpeed=this->parent->maxWalkSpeed;
    std::vector<GLfloat> newVertices(this->parent->vertices);
//    this->vertices = this->parent->vertices;
    this->vertices = newVertices;
    std::vector<GLuint> newIndices(this->parent->indices);
//    this->indices = this->parent->indices;
    this->indices = newIndices;
//    std::vector<GLfloat> newVerticesDead(this->parent->verticesDead);
//    this->verticesDead = this->parent->verticesDead;
//    this->verticesDead = newVerticesDead;
//    std::vector<GLuint> newIndicesDead(this->parent->indicesDead);
//    this->indicesDead = this->parent->indicesDead;
//    this->indicesDead = newIndicesDead;
//    loadObj::load(filename,&this->vertices, &this->indices);
//   this->bindBuffers(true);
    this->buffers = this->parent->buffers;
    this->currentBinding = this->parent->currentBinding;
//    this->bindBuffers(5,8,GL_STATIC_DRAW);
    this->texture2D = this->parent->texture2D;
//    this->texture2DDead = this->parent->texture2DDead;
//    this->bindTexture2D("../src/img/catTX.png");
    this->lightMap = this->parent->lightMap;
//    this->lightMapDead = this->parent->lightMapDead;
//    this->bindLightMap2D("../src/img/light/example.png");
    this->shadowMap = this->parent->shadowMap;
//    this->shadowMapDead = this->parent->shadowMapDead;
//    this->bindShadwMap2D("../src/img/shadow/example.png");
    this->startLook = this->parent->startLook;
//    this->startLook = glm::vec3(1.0f,0.0f,0.0f);

    this->weapon = new Gun( (char*)"../src/obj/weapon.obj",10,100,this);

    this->size.y=this->parent->size.y;
//    this->size.y=1.33;
    this->size.x=this->parent->size.x;
//    this->size.x=1.33;
    this->size.z=this->parent->size.z;
//    this->size.z=0.66;
}


Caterpillar::~Caterpillar(){
    delete this->weapon;
    std::cout << "Caterpillar deleted" << std::endl;
}

void Caterpillar::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->modM=this->posM*this->rotMY*this->sclM;

      if( this->dead==1 ){
//         printf("DEAD\n" );
         this->vertices=this->box->vertices;
         this->indices=this->box->indices;
         this->texture2D=this->box->texture2D;
         this->lightMap=this->box->lightMap;
         this->shadowMap=this->box->shadowMap;
         this->dead=2;
          this->buffers = this->box->buffers;
          this->currentBinding = this->box->currentBinding;
//         this->bindBuffers(5,8,GL_STATIC_DRAW);
      }

   Object::draw(projection,modelView,lights,sun);
    if(this->dead==0){
//      printf("DEAD: %d\n",this->dead);
        this->weapon->draw(projection,modelView,this,lights,sun);
        if(this->font!= NULL){
            glm::mat4 temp = this->posM;
            this->font->projection = projection;
            this->font->view = modelView;
            this->font->rotMY = this->rotMY;
            temp[3][0] += 0.0f;
            temp[3][1] += 10.0f;
            temp[3][2] += 0.0f;
            this->font->posM = temp;
            //      this->font->print3d("+"+std::to_string(this->life),10.0f,0.0f,0.01f,glm::vec3(1.0f,0.0f,0.0f));
            this->font->print3d(this->getLife(),0.0f,0.0f,0.01f,this->player->kolor);
        }
    }
}


std::string Caterpillar::getLife() {
    std::string temp;
    if(this->life >=0){
        temp="+";
    }
    temp +=std::to_string(this->life);
    return temp;
}

void Caterpillar::dealDamage(int damage) {
    std::cout <<"Bullete damage: " << damage << std::endl;
    this->life -= damage;
    if(this->life <= 0){
        this->dead = 1;
//        Caterpillar* temp = nullptr;
//        std::vector<Caterpillar*> temp2 = this->player->aliveCaterpillars;
        std::vector<Caterpillar*>::iterator it = std::find(this->player->aliveCaterpillars.begin(),this->player->aliveCaterpillars.end(),this);
        if(it != this->player->aliveCaterpillars.end()){
            std:: cout << "Caterpillar of player: " << this->player->nazwa << " died life: " << this->life << std::endl;
            this->player->aliveCaterpillars.erase(it);
        }
    }
}

void Caterpillar::heal(int heal) {
    std::cout << "Healed: " << heal << std::endl;
    if(this->life > 0){
        this->life += heal;
    }

}
