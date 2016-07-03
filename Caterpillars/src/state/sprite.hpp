//
// Created by lewin on 03.07.16.
//
#ifndef SPRITE
#define SPRITE

#include "object2D.hpp"

class Sprite : public object2D{
public:
   Sprite(float x, float y, float width, float height, GLchar *fileName);
};

#endif //CATERPILLARS_SPRITE_HPP
