//
// Created by lewin on 03.07.16.
//

#include "sprite.hpp"

Sprite::Sprite(float x, float y, float width, float height, GLchar *fileName)  : object2D(x,y,width,height,fileName){
    this->shader = new Shader("../src/shaders/2dTex.vs","../src/shaders/2dTex.frag");
}