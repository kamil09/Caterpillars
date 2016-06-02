#ifndef INFO
#define INFO

#include "font.hpp"
#include "vector"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <glm/glm.hpp>
#include "errorGL.hpp"

class Text {
public:
    Text(std::string newText,float newX,float newY,float newSkala);
    std::string text;
    float x;
    float y;
    float skala;
    void draw(Font *font);
};

class Info {
public:
    Info(GLFWwindow* window);
    ~Info();
    Font *font;
    // std::vector<std::string> name;
    std::vector<Text*> texty;
    void fps();
    void initFps();
    unsigned int addText(std::string newText,float newX,float newY,float newSkala);
    int nbFrames = 0;
    double lastTime;
    void draw();
    unsigned int fpsIndex;
};
#endif
