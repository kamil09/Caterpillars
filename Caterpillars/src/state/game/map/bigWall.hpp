#ifndef wallCl
#define wallCl

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
// #include "../../../inputActions.hpp"

using namespace std;

//MAPA MOŻE BYĆ TYLKO JEDNA :)
class Wall : public Object{
private:
   void recalculateTriangleMap();
public:
   //deprecated
   Wall(int x, int width, int z, int depth, int min, int max);
   Wall(char *filename, int x, int width, int z, int depth, int min, int max);
   ~Wall();

//   void bindBuffers(bool newBuffer);
   void draw(glm::mat4 projection, glm::mat4 modelView);
};

#endif
