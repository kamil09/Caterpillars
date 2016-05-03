#ifndef button
#define button

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   -1.0f, -1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f,
};

class Button{

public:
   Button();
   ~Button();
   int posX;
   int posY;
   int width;
   int height;


};

#endif
