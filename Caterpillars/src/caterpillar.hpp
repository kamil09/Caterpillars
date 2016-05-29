#ifndef caterpillarCl
#define caterpillarCl

#include "object.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "loadData/loadOBJ.hpp"


class Caterpillar : public Object{
private:
   float life;          //Życie naszego bohatera :)
   float maxWalkAngle;  //Maksymalny kąt pod jakim może wchodzić worms na wzniesienie
public:
   Caterpillar(char *filename);
   ~Caterpillar();
   void bindBuffers(bool newBuffer);
   void draw(glm::mat4 projection, glm::mat4 modelView);
   void setPos(float x,float y,float z);
   glm::vec3 startLook;
   float maxWalkSpeed;  //maksymalna prędkość chodzenia m/s
   float viewBack;
};

#endif
