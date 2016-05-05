#include "map.hpp"

/**
 * Ustawienia mapy i genearatora
*/
const int vertX=2000;
const int vertY=2000;
const int baseHeight=50;
const int maxMapHeight=400;
const int maxHillRadius=300;
const int minHillNum=10;
const int maxHillNum=25;

Map::Map(){
   srand (time(NULL));
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
   this->fogHeight=0;

   this->rand();
   this->generateRandomMap();
   this->genTriangleTab();
}
Map::~Map(){}

void makeHill(float **map){
   float hillHeight = rand() % maxMapHeight;
   float hillRadius = rand() % maxHillRadius;
   float hillGeometry = ((rand() % 101)-50)/50;
   printf("hillH:%f hillRad:%f hillGeo:%f \n",hillHeight,hillRadius,hillGeometry);
}

void Map::generateRandomMap(){
   //DEKLARACJA PAMIĘCI I USTAWIENIE BAZOWEJ WYSOKOŚCI
   this->mapVert = new float*[vertX];
   for(int i=0;i<vertX;i++) mapVert[i]=new float[vertY];
   for(int i=0;i<vertX;i++)
      for(int j=0;j<vertY;j++)
         this->mapVert[i][j]=baseHeight;

   //WYLOSOWANIE n WZNIESIEN I URUCHOMIENIE n WĄTKÓW BUDOWY WZNIESIENIA
   int hillNumbers = rand() % (maxHillNum-minHillNum) + minHillNum;

   std::vector<std::thread*> threadList;
   //threads fight : START
   for(int i=0;i<hillNumbers;i++)
      threadList.push_back(new std::thread(makeHill,this->mapVert));

   for(int i=0;i<hillNumbers;i++){
      threadList[i]->join();
      delete threadList[i];
   }

}
void Map::rand(){

}
void Map::kaboom(float x, float y, float z, float radius){
   //Zmniejszamy wysokość w punkcie kaboom i okolicznych
   //Dajemy efekt dźwiękowy i odpryski jakieś.

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
