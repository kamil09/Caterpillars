//
// Created by lewin on 03.07.16.
//

#include "text.hpp"

Text::Text(std::string newText,float newX,float newY,float newSkala,glm::vec3 color){
    this->text = newText;
    this->x = newX;
    this->y = newY;
    this->skala = newSkala;
    this->kolor = color;
}

void Text::draw(Font *font){
    font->print(this->text,this->x,this->y, this->skala,this->kolor);
}
