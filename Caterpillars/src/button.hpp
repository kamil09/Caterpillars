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
    const GLchar *vertexShaderSource;
    const GLchar *fragmentShaderSource;
   // Button(int i,GLfloat lewaKrawedz,GLfloat prawaKrawedz,GLfloat gornaKrawedz,GLfloat dolnaKrawedz);
   Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight);
   ~Button();
   // GLfloat vertices[12];
   //
   // GLuint indices[6];
   // GLfloat posX;
   // GLfloat posY;
   GLfloat width;
   GLfloat height;

   // GLuint VAO;
   // GLuint VBO;
   // GLuint EBO;
   // GLuint shaderProgram;

   GLfloat r;
   GLfloat g;
   GLfloat b;

void initVertexShaderSource();
void initFragmentShaderSource();
void initProgram();
void bindBuffers();
void rysuj();
void wybrano();

};

#endif
