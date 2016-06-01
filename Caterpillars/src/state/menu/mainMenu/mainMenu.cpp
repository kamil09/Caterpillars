#include "mainMenu.hpp"
#include "../../../inputActions.hpp"

void singlePlayer(GLFWwindow* window,GLFWcursor* cursor);
void multiPlayer(GLFWwindow* window,GLFWcursor* cursor);

void options(GLFWwindow* window,GLFWcursor* cursor);

void exitWindow(GLFWwindow* window,GLFWcursor* cursor);

MainMenu::MainMenu(GLFWwindow *window,GLFWcursor *cur) : Menu(window,cur){
	// this->callBackArray.push_back(this->singlePlayer);
	this->callBackArray.push_back(singlePlayer);
	this->callBackArray.push_back(multiPlayer);
	this->callBackArray.push_back(options);
	this->callBackArray.push_back(exitWindow);
	// this->callBackArray = ;
	// this->callBackArray[]{
	//     MainMenu::singlePlayer,
	//     MainMenu::multiPlayer,




	//     MainMenu::options,
	//     MainMenu::exitWindow
	// };
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

void singlePlayer(GLFWwindow* window,GLFWcursor* cursor){
	std::cout << "Single Player!" << std::endl;
	inputActions::getInstance().changeGame(window, cursor);
}
void multiPlayer(GLFWwindow* window,GLFWcursor* cursor){
	std::cout << "MultiPlayer!" << std::endl;
}

void options(GLFWwindow* window,GLFWcursor* cursor){
	// this->callBackArray.push_back(static_cast(MainMenu::singlePlayer));
	std::cout << "Options!" << std::endl;
}

void exitWindow(GLFWwindow* window,GLFWcursor* cursor){
	std::cout << "Exit window!" << std::endl;
	glfwSetWindowShouldClose(window, GL_TRUE);

}
