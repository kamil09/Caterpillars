#include "map.hpp"

Map::Map(){
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
   this->fogHeight=0;

   this->rand();
   this->genTriangleTab();
}
Map::~Map(){

}
void Map::rand(){

}
void Map::kaboom(float x, float y, float z, float radius){
   //Zmniejszamy wysokość w punkcie kaboom i okolicznych

   this->genTriangleTab();
}
void Map::genTriangleTab(){
   //Z mapVert[][] generujemy siatkę trójątów na początku i po każdym niszeniu terenu
}
Map& Map::getInstance(){
	static Map instance;
	return instance;
}

void Map::draw(){
   //Rysujemy i teksturujemy mapę
   //Rysujemy i teksturujemy mur (4 pionowe sciany)
   //Rysujemy mgłę zamiast wody lub wodę :)
}
