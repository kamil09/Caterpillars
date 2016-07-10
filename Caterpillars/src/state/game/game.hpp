#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"
#include "map/bigWall.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../../object.hpp"
#include "../../models/caterpillar.hpp"
#include "../../models/tower.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "../object2D.hpp"
#include "../sprite.hpp"


class Game : public State{
private:
   void drawRose();
   void calcViewMatrix();
   Map *map;
   Wall *wall;
   std::vector<Tower*> towers;
//   object2D *targetView;
   Sprite *targetView;
//   object2D *rose;
   Sprite *rose;
   std::vector< Caterpillar* > caterrVec;
   Caterpillar* currentCutterpillar;
   void testViewMov();
   void catterMove();
   clock_t start, end;
public:
   Game(GLFWwindow *window,GLFWcursor *cur);
   void run() override;
   void draw() override;

   glm::mat4 projection;   //perspektywa
   glm::mat4 modelView;    //cała maciez kamery
   glm::vec3 lookAt;       //na co patrzymy
   glm::vec3 lookFrom;     //umiejscowanie kamery

   glm::mat4 lightsMat;

   static int currCatIndex;

   /**
   * Funkcja sprawdza kolizję oraz przesuwa objekt jeżeli może
   * Zwraca kolizję na Osi Y
   */
   static bool checkCollisionAndMove(Object *o,float x, float y, float z, std::vector<Object*> v );
   static bool checkCollisionAndMove(Object *o,glm::vec3 pos, std::vector<Object*> v);

};

#endif
