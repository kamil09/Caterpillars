#ifndef MAIN_MENU
#define MAIN_MENU

#include "../menu.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class MainMenu : public Menu{
public:
    MainMenu(GLFWwindow *window,GLFWcursor *cur);
    void loadTextureFiles() override;
    // ~MainMenu();
};

#endif
