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
    static Bullet *parent;
   Bullet(char *filename, float shotPower);
   Bullet(char *filename);
   ~Bullet();
   void draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights, glm::vec4 sun);
   glm::vec3 startLook;
   int damage = 100;
    float shotPower;
    void recalculateRotZ();
   bool used;
    void copyParent();
    float currentWaitTime = -1.0f;
    float waitTime = 5.0f;
};

#endif
