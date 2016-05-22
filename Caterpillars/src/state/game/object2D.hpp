#ifndef Object2D
#define Object2D

#include "../../object.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../inputActions.hpp"

using namespace std;

//MAPA MOŻE BYĆ TYLKO JEDNA :)
class object2D : public Object{

public:
   object2D(float x, float y, float width, float height, GLchar *fileName);
   ~object2D();

   void bindBuffers();
   void draw();
   void setTraM(float x,float y,float z);
};

#endif
