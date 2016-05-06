#ifndef MENU
#define MENU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../button.hpp"
#include "../errorGL.hpp"
#include "../state.hpp"

// #include "inputActions.hpp"


class Menu : public State{
public:
    Menu(GLFWwindow *window);
    std::vector<Button*> listaButtonow;
    int buttonCount;
    void draw() override;
    void draw2();
    void run() override;
    void pressESC() override;
    void releaseLMB() override;
    void readPixel(GLFWwindow *window);
    // void addNewButton();
    void createButtons(int count);
};

#endif
