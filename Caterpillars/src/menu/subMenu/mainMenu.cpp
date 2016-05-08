#include "mainMenu.hpp"

MainMenu::MainMenu(GLFWwindow *window) : Menu(window){
    this->createBackgroud("../src/img/menuBack.png");
    this->loadTextureFiles();
    this->buttonWidth = 0.5f;
    this->buttonHeight = 0.3f;
    this->buttonDistance = 0.25f;
    this->createButtons(4, 0.0f, 0.6f);
}
