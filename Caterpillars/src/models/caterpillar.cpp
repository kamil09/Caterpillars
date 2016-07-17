#include "caterpillar.hpp"


Caterpillar* Caterpillar::parent = nullptr;

Caterpillar::Caterpillar(char *filename){
    std::cout << "###TWORZENIE CATERPILLARA###" << std::endl;
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
   this->bindLightMap2D("../src/img/light/catLight.png");
   this->bindShadwMap2D("../src/img/shadow/example.png");
   this->startLook = glm::vec3(1.0f,0.0f,0.0f);

   this->weapon = new Gun( (char*)"../src/obj/weapon.obj",10,100,this);

   this->size.y=1.33;
   this->size.x=1.33;
   this->size.z=0.66;
}


Caterpillar::Caterpillar(Player *player, char *filename) {
    this->player = player;
    if(Caterpillar::parent== nullptr){
        Caterpillar::parent = new Caterpillar(filename);
    }
    this->copyParent();
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

    this->windMul=this->parent->windMul;
    this->life=this->parent->life;
    this->maxWalkAngle=this->parent->maxWalkAngle;
    this->maxWalkSpeed=this->parent->maxWalkSpeed;
    this->vertices = this->parent->vertices;
    this->indices = this->parent->indices;
//    loadObj::load(filename,&this->vertices, &this->indices);
//   this->bindBuffers(true);
    this->buffers = this->parent->buffers;
    this->currentBinding = this->parent->currentBinding;
//    this->bindBuffers(5,8,GL_STATIC_DRAW);
    this->texture2D = this->parent->texture2D;
//    this->bindTexture2D("../src/img/catTX.png");
    this->lightMap = this->parent->lightMap;
//    this->bindLightMap2D("../src/img/light/example.png");
    this->shadowMap = this->parent->shadowMap;
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


Caterpillar::~Caterpillar(){}

void Caterpillar::setPos(float x,float y,float z){
   this->pos.x=x;
   this->pos.y=y;
   this->pos.z=z;
   this->recalculateMatrix();
}

void Caterpillar::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
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
//        this->font->print3d("+"+std::to_string(this->life),10.0f,0.0f,0.01f,glm::vec3(1.0f,0.0f,0.0f));
        this->font->print3d(this->getLife(),0.0f,0.0f,0.01f,this->player->kolor);
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

