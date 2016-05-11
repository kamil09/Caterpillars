#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Game : public State{
public:
   Game(GLFWwindow *window,GLFWcursor *cur);
   void run() override;
   void draw() override;
   Map *map;
   void testViewMov();

   glm::mat4 projection;   //perspektywa
   glm::mat4 modelView;    //cała maciez kamery
   glm::vec3 lookAt;       //na co patrzymy
   glm::vec3 lookFrom;     //umiejscowanie kamery
};

#endif
