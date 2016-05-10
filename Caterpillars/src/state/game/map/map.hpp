#ifndef mapCl
#define mapCl

#include "../../../object.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../../inputActions.hpp"

using namespace std;

//MAPA MOŻE BYĆ TYLKO JEDNA :)
class Map : public Object{
private:
   float windForce; //predkosc wiatru [m/s]
   float gravity;   //grawitacja [m/s^2]
   float fogSpeed;  //Prędkość podnoszenia się mgły [m/s] (zamiast wody :) )
   float fogHeight; //Wysokość na jakiej jest mgła
   float air;       //Współczynnik Oporu powietrza Od 0 do 1
   float **mapVert; //Jedna jednostka - 0,5 metra (1000m x 1000m) wartość w tablicy - wysokość
   int minHeight;   //wysokość do jakiej można rozwalić teren
   void generateRandomMap();
   void recalculateTriangleMap();

   glm::mat4 projection;   //perspektywa
   glm::mat4 modelView;    //cała maciez kamery
   glm::vec3 lookAt;       //na co patrzymy
   glm::vec3 lookFrom;     //umiejscowanie kamery
public:
   Map();
   ~Map();
   void bindBuffers(bool newBuffer);
   Map(const Map &);
   static Map& getInstance();
   void draw();
   void rand();     //Losuje wiatr itp
   void kaboom(float x, float y, float z, float radius);    //Robi kaboom na mapie
   void genTriangleTab();
   void testViewMov();
};

#endif
