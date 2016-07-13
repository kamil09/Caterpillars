#ifndef bulletCl
#define bulletCl

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


class Bullet : public Object{
private:

public:
   Bullet(char *filename, float randDam);
   ~Bullet();
   void draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights, glm::vec3 sun);
   void setPos(float x,float y,float z);
   glm::vec3 startLook;
   float Damage;
   bool used;

};

#endif
