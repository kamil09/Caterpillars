#ifndef button
#define button

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <glm/glm.hpp>
#include "../object.hpp"
#include "../errorGL.hpp"
#include "../shader.hpp"

class Button : public Object{

public:
    // Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight,std::string texturePath);
    Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight,const char* texturePath);
   ~Button();
   GLfloat width;
   GLfloat height;
   GLfloat r;
   GLfloat g;
   GLfloat b;
void bindBuffers();
void bindBuffers2();
void draw();
void draw2();
void select();

};

// const GLchar *Button::vertexPath = "./shader.vs";
// const GLchar *Button::fragmentPath = "./shader.frag";

#endif
