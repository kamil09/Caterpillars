#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"
#include "map/bigWall.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../../object.hpp"
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
   void testViewMov();

   glm::mat4 projection;   //perspektywa
   glm::mat4 modelView;    //cała maciez kamery
   glm::vec3 lookAt;       //na co patrzymy
   glm::vec3 lookFrom;     //umiejscowanie kamery


   bool checkMapCollisionX(Object o);
   bool checkMapCollisionY(Object o);
   bool checkMapCollisionZ(Object o);
   bool checkMapCollisionX(float k);
   bool checkMapCollisionY(float k);
   bool checkMapCollisionZ(float k);

};

#endif
