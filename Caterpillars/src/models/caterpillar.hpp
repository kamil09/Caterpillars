#ifndef caterpillarCl
#define caterpillarCl

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
#include "gun.hpp"
#include "../font.hpp"
#include "../state/game/player.hpp"


class Caterpillar : public Object{
private:
   float maxWalkAngle;  //Maksymalny kąt pod jakim może wchodzić worms na wzniesienie
public:
   static Caterpillar *parent;
   void copyParent();
   Caterpillar(char *filename);
   Caterpillar(Player *player,char *filename);
   ~Caterpillar();
   void draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun);
   glm::vec3 startLook;
   float maxWalkSpeed;  //maksymalna prędkość chodzenia m/s
   float viewBack;
   float tmpViewBack;
   Player *player;
   Gun *weapon;
   Font *font;
   int life;//Życie naszego bohatera :)
    std::string getLife();
};


#endif
