#ifndef objectCl
#define objectCl

class Object{
private:
   float speedX;
   float speedY;
   float speedZ;
   float posX;
   float posY;
   float posZ;
   double kickTime;  //Czas od rozpoczęcia rzutu

public:
   Object();
   ~Object();
   void draw();
   float windMul; // od 0 do 1. Jak wiatr wpływa na dany obiekt. Dla mapy np 0, dla pocisku 1 a dla robala delikatnie
   void kick(float x,float y, float z);
   void recalculatePhysics();
};

#endif
