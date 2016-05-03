#include "map.hpp"

Map::Map(){
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
}
Map::~Map(){

}

Map& Map::getInstance(){
	static Map instance;
	return instance;
}

void Map::draw(){

}
