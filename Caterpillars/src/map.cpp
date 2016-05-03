#include "map.hpp"

Map::Map(){
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
}
Map::~Map(){

}

Map& Map::getInstance(){
	static Map instance;
	return instance;
}

void Map::draw(){

}
