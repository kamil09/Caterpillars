#ifndef Object2D
#define Object2D

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
#include "../text.hpp"
#include "../font.hpp"
using namespace std;

//MAPA MOŻE BYĆ TYLKO JEDNA :)
class object2D : public Object{

public:
   object2D(float x, float y, float width, float height, string fileName);
   object2D(float x, float y, float width, float height, glm::vec4 color);
   ~object2D();
    void initObject2D(float x, float y, float width, float height, string fileName);

    glm::vec4 kolor;
//   void bindBuffers();
   virtual void draw();
   void setTraM(float x,float y,float z);
   std::vector<Text*> teksty;
    Font *font = NULL;
    void initFont(const char *ttf, int size);
    unsigned int addText(std::string newText, float newX, float newY, float newSkala, glm::vec3 kolor);
    unsigned int addTextL(std::string newText, float newX, float newY, float newSkala, glm::vec3 kolor);
    unsigned int addTextM(std::string newText, float newX, float newY, float newSkala, glm::vec3 kolor);
    unsigned int addTextLM(std::string newText, float newX, float newY, float newSkala, glm::vec3 kolor);
   virtual void inUniform(){}
    virtual void drawText();
};

#endif
