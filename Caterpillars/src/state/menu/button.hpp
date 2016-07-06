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
#include "../../errorGL.hpp"
#include "../../shaders/shader.hpp"
#include "../object2D.hpp"
#include <functional>
#include "../state.hpp"

class Button : public object2D{

public:
    // Button(int i,GLfloat newX, GLfloat newY, GLfloat newWidth,GLfloat newHeight,std::string texturePath);
//    Button(int i,GLfloat newX, GLfloat newY,GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath, std::function<void(GLFWwindow*,GLFWcursor*)> callBack);
//    Button(int i,GLfloat newX, GLfloat newY,GLfloat newZ, GLfloat newWidth,GLfloat newHeight,const char* texturePath, std::function<void(GLFWwindow*,GLFWcursor*)> callBack);
    Button(int index, float x, float y, float width, float height, GLchar *fileName,
           std::function<void(State *,GLFWwindow *, GLFWcursor *)> callBack);
    ~Button();
   GLfloat r;
   GLfloat g;
   GLfloat b;
    int check;
//void draw(int check);

// void select();
// void (*callBackFunction)(void);
std::function<void(State *,GLFWwindow*,GLFWcursor*)> callBackFunction;
    void inUniform() override;
};

// const GLchar *Button::vertexPath = "./shader.vs";
// const GLchar *Button::fragmentPath = "./shader.frag";

#endif
