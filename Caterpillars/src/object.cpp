#include "object.hpp"

Object::Object(){
   this->windMul=0;
   this->speedX=0;
   this->speedY=0;
   this->speedZ=0;
   this->kickTime=0;
}
Object::~Object(){

}

void Object::draw(){

};

void Object::kick(float x,float y, float z){
   this->speedX=x;
   this->speedY=y;
   this->speedZ=z;
   //this->kickTime=time_now??;

}
void Object::recalculatePhysics(){
   //this->kickTime=???
   //Wzorek na rzut ukośny mając prędkości początkowe i czas wyliczamy nowe współrzędne
   //Sprawdzanie kolizji (czy można przesunąć obiekt na daną pozycję)

}
