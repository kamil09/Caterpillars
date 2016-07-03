//
// Created by lewin on 03.07.16.
//

#ifndef TEXT
#define TEXT
#include "vector"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <glm/glm.hpp>
#include "errorGL.hpp"
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "font.hpp"

class Text {
public:
    Text(std::string newText,float newX,float newY,float newSkala,glm::vec3 color);
    std::string text;
    float x;
    float y;
    float skala;
    glm::vec3 kolor;
    void draw(Font *font);
};

#endif //CATERPILLARS_TEXT_HPP
