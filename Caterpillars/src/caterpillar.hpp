#ifndef caterpillarCl
#define caterpillarCl

#include "object.hpp"

class Caterpillar : public Object{
private:
   float life;          //Życie naszego bohatera :)
   float maxWalkAngle;  //Maksymalny kąt pod jakim może wchodzić worms na wzniesienie
   float maxWalkSpeed;  //maksymalna prędkość chodzenia m/s
public:
   Caterpillar();
   ~Caterpillar();
   void draw();
};

#endif
