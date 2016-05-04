#ifndef objectCl
#define objectCl

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

class Object{
private:
   float speedX;
   float speedY;
   float speedZ;
   float posX;
   float posY;
   float posZ;
   bool canKick;     //Czy można zadziałać na dany obiekt. Jezeli false to obiekt znajduje się w powietrzu i nie da rady w niego ingerować
   double kickTime;  //Czas od rozpoczęcia rzutu

   int verticlesCount;
   GLfloat vertices[];
   GLuint indices[];
public:
   Object();
   ~Object();
   void draw();
   float windMul; // od 0 do 1. Jak wiatr wpływa na dany obiekt. Dla mapy np 0, dla pocisku 1 a dla robala delikatnie
   void kick(float x,float y, float z);
   void recalculatePhysics();
};

#endif
