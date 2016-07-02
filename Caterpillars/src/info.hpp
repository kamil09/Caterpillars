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
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    struct sysinfo meminfo;
    // std::vector<std::string> name;
    // std::vector<Text*> texty;
    std::map<char,Text*> texty;
    int freeIndex = 0;
    bool showFps = true;
    bool showRam = true;
    bool showCpu = true;
    bool showVRam = true;
    bool showUsage = true;
    void fps();
    void initFps();
    unsigned int addText(std::string newText,float newX,float newY,float newSkala,char index);
    int nbFrames = 0;
    double lastTime;
    void draw();
    // unsigned int fpsIndex;
    void usage();
    void virtualMemory();
    void physicalMemory();
    void cpu();
    int extractNumber(char *line);
    int getValue(const char* fileDir,const char* text);
};
#endif
