#ifndef gunCl
#define gunCl

#include "../object.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../loadData/loadOBJ.hpp"

class Gun : public Object{
private:

public:
   Gun(char *filename, float min, float max,Object *owner);
   ~Gun();
   void draw(glm::mat4 projection, glm::mat4 modelView, Object *owner, glm::mat4 lights,glm::vec3 sun);
   void setPos(float x,float y,float z);
   glm::vec3 startLook;
   float viewBack;
   float tmpViewBack;
   float minDamage;
   float maxDamage;
   glm::mat4 posMadd;   //Maciez przesuniecia
};

#endif
