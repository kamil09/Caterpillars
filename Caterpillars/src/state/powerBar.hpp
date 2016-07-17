//
// Created by lewin on 17.07.16.
//

#ifndef POWERBAR
#define POWERBAR

#include "sprite.hpp"

class PowerBar : public Sprite{
public:
    void draw(int shotPower);

    PowerBar(float x, float y, float width, float height, string fileName);
};

#endif //CATERPILLARS_POWERBAR_HPP
