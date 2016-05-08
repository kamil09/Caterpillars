#ifndef MAIN_MENU
#define MAIN_MENU

#include "../menu.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainMenu : public Menu{
public:
    MainMenu(GLFWwindow *window);
    // ~MainMenu();
};

#endif
