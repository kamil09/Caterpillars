#include "mainMenu.hpp"

MainMenu::MainMenu(GLFWwindow *window) : Menu(window){
    this->loadTextureFiles();
    this->createBackgroud("../src/img/menuBack.png");
    this->buttonWidth = 0.5f;
    this->buttonHeight = 0.3f;
    this->buttonDistance = 0.25f;
    this->createButtons(4, 0.0f, 0.6f);
}


void MainMenu::loadTextureFiles(){
    this->listaTekstur.push_back("../src/img/menuLab1.png");
    this->listaTekstur.push_back("../src/img/menuLab2.png");
    this->listaTekstur.push_back("../src/img/menuLab3.png");
    this->listaTekstur.push_back("../src/img/menuLab4.png");
}
