//
// Created by lewin on 03.07.16.
//

#include "sprite.hpp"

Sprite::Sprite(float x, float y, float width, float height, string fileName) : object2D(x, y, width, height,
                                                                                        fileName) {
    this->shader = new Shader("../src/shaders/2dTex.vs","../src/shaders/2dTex.frag");
}


Sprite::Sprite(float x, float y, float width, float height, glm::vec4 color) : object2D(x,y,width,height,color) {
    this->shader = new Shader("../src/shaders/2dTex.vs","../src/shaders/2dTexColor.frag");

}

