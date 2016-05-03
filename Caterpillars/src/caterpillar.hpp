#ifndef caterpillarCl
#define caterpillarCl

#include "object.hpp"

class Caterpillar : public Object{
private:
   float life;

public:
   Caterpillar();
   ~Caterpillar();
   void draw();
};

#endif
