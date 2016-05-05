#ifndef button
#define button

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "object.hpp"

class Button : public Object{

public:
    Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight);
   ~Button();
   GLfloat width;
   GLfloat height;
GLfloat r;
   GLfloat g;
   GLfloat b;
void bindBuffers();
void rysuj();
void wybrano();

};

// const GLchar *Button::vertexPath = "./shader.vs";
// const GLchar *Button::fragmentPath = "./shader.frag";

#endif
