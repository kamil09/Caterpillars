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
	this->loadTextureFiles();
    this->loadCoordinates();
	this->createBackgroud("../src/img/menuBack.png");
	this->createButtons();
}


void MainMenu::loadTextureFiles(){
	this->listaTekstur.push_back("../src/img/single.png");
	this->listaTekstur.push_back("../src/img/multi.png");
	this->listaTekstur.push_back("../src/img/options.png");
	this->listaTekstur.push_back("../src/img/exit.png");
}

void MainMenu::loadCoordinates() {
//    GLint viewport[4];
//    glGetIntegerv(GL_VIEWPORT, viewport);
	this->listaWspolrzednych.push_back(glm::vec4(0,0,363.2148806219,76.9572459745));
	this->listaWspolrzednych.push_back(glm::vec4(0,0,350,77.7345918934));
	this->listaWspolrzednych.push_back(glm::vec4(0,0,257.3014991671,61.6046640755));
	this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
    this->loadTranslates();
}
 
void MainMenu::loadTranslates() {
    float lewyMargines = (-this->windowXsize/2)+25;
    float yFirstButton = -100;
    float distance = 15;
    for (unsigned int i = 0; i<this->listaWspolrzednych.size();i++){
        float temp=0;
//        if(i!=0){
            temp = temp + i*distance;
            for(int j=1;j<=i ;j++){
                temp = temp + listaWspolrzednych[j].w;
            }
//        }
        float y = yFirstButton - temp;
        this->listaPrzesuniec.push_back(glm::vec3(lewyMargines,y,0));

    }
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
