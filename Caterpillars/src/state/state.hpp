#ifndef STATE
#define STATE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include "inputActions.hpp"
#include <iostream>
// #include "../inputActions.hpp"

class State{
public:
    State(GLFWwindow *currentWindow,GLFWcursor *cur);
    GLFWwindow *window;
    GLFWcursor *cursor;
    int windowXsize;
    int windowYsize;
    virtual void draw() = 0;
    virtual void run() = 0;
    void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods );
    void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    bool customPollEvents;

    //Obsluga klawiatury:
    //WSAD
    virtual void pressW(){}
    virtual void releaseW(){}
    virtual void pressS(){}
    virtual void releaseS(){}
    virtual void pressA(){}
    virtual void releaseA(){}
    virtual void pressD(){}
    virtual void releaseD(){}
    //Space
    virtual void pressSpace(){}
    virtual void releaseSpace(){}
    //I
    virtual void pressI(){}
    virtual void releaseI(){}
    //ESC
    virtual void pressESC(){}
    virtual void releaseESC(){}

    //Obsluga myszy:
    //LMB i RMB
    virtual void pressLMB(){}
    virtual void releaseLMB(){}
    virtual void pressRMB(){}
    virtual void releaseRMB(){}
};



#endif
