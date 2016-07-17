//
// Created by lewin on 17.07.16.
//

#include "powerBar.hpp"


PowerBar::PowerBar(float x, float y, float width, float height, string fileName) : Sprite(x,y,width,height,fileName) {
}


void PowerBar::draw(int shotPower) {
    float x = this->pos.x;
    float y = this->pos.y;
    float xTex = shotPower/100.0f;
    float width = this->size.x*xTex;
    float height = this->size.y;
    this->vertices = {
            x, y, 0.0f, 0.0f, 0.0f,
            x+width, y,  0.0f, xTex, 0.0f,
            x, y+height, 0.0f, 0.0f, 1.0f,
            x+width, y+height, 0.0f, xTex, 1.0f,
    };
    this->indices = {
            0,1,2,3
    };
    this->bindBuffers(5,5,GL_DYNAMIC_DRAW);
    object2D::draw();
}

