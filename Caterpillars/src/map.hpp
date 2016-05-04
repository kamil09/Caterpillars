#ifndef mapCl
#define mapCl

#include "object.hpp"

//MAPA MOŻE BYĆ TYLKO JEDNA :)
class Map : public Object{
private:
   float windForce; //predkosc wiatru [m/s]
   float gravity;   //grawitacja [m/s^2]
   int minHeight;   //minimalna wysokość do jakiej można rozwalić teren
   float fogSpeed;  //Prędkość podnoszenia się mgły [m/s] (zamiast wody :) )
   float air;       //Współczynnik Oporu powietrza

public:
   Map();
   ~Map();
   Map(const Map &);
   static Map& getInstance();
   void draw();
};

#endif
