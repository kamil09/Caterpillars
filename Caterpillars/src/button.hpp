#ifndef button
#define button

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
// static const GLfloat g_vertex_buffer_data[] = {
//    -1.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 0.0f,
//    1.0f,  1.0f, 0.0f,
//    1.0f,  1.0f, 0.0f,
//    -1.0f, -1.0f, 0.0f,
//    -1.0f, 1.0f, 0.0f,
// };




class Button{

public:
    const GLchar *vertexShaderSource;
    const GLchar *fragmentShaderSource;
   Button();
   ~Button();
   GLfloat vertices[12];
   GLuint indices[6];
   int posX;
   int posY;
   int width;
   int height;
   void initVertexShaderSource();
   void initFragmentShaderSource();
   void initProgram();
   void bindBuffers();
   void rysuj();
   GLuint VAO;
   GLuint VBO;
   GLuint EBO;
   GLuint shaderProgram;
};

#endif
