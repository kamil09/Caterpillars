#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"
#include "map/bigWall.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../../object.hpp"
#include "../../caterpillar.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object2D.hpp"

class Game : public State{
private:
   void drawRose();
public:
   Game(GLFWwindow *window,GLFWcursor *cur);
   void run() override;
   void draw() override;
   Map *map;
   Wall *wall;
   object2D *targetView;
   object2D *rose;
   std::vector< Caterpillar* > caterrVec;
   Caterpillar* currentCutterpillar;
   void testViewMov();
   void catterMove();

   glm::mat4 projection;   //perspektywa
   glm::mat4 modelView;    //cała maciez kamery
   glm::vec3 lookAt;       //na co patrzymy
   glm::vec3 lookFrom;     //umiejscowanie kamery


    static bool checkMapCollisionX(Object o);
    static bool checkMapCollisionY(Object o);
    static bool checkMapCollisionZ(Object o);
    static bool checkMapCollisionX(float k);
    static bool checkMapCollisionY(float k);
    static bool checkMapCollisionZ(float k);

};

#endif
