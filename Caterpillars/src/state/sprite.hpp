//
// Created by lewin on 03.07.16.
//
#ifndef SPRITE
#define SPRITE

#include "object2D.hpp"

class Sprite : public object2D{
public:
   Sprite(float x, float y, float width, float height, string fileName);
   Sprite(float x, float y, float width, float height, glm::vec4 color);
};

#endif //CATERPILLARS_SPRITE_HPP
