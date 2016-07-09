#include "mainMenu.hpp"
#include "../../../inputActions.hpp"

void singlePlayer(Button *state, GLFWwindow *window, GLFWcursor *cursor);
void multiPlayer(Button *state, GLFWwindow *window, GLFWcursor *cursor);

void options(Button *state, GLFWwindow *window, GLFWcursor *cursor);

void exitWindow(Button *state, GLFWwindow *window, GLFWcursor *cursor);

MainMenu::MainMenu(GLFWwindow *window,GLFWcursor *cur) : Menu(window,cur){
	// this->callBackArray.push_back(this->singlePlayer);
	this->loadCallBacks();
//	this->callBackArray.push_back(singlePlayer);
//	this->callBackArray.push_back(multiPlayer);
//	this->callBackArray.push_back(options);
//	this->callBackArray.push_back(exitWindow);
	this->loadTextureFiles();
    this->loadCoordinates();
	this->createBackgroud("../src/img/menuBack.png");
//	this->createBackgroud(NULL);
	this->createButtons();
	this->loadSprites();
}


void MainMenu::loadSprites() {
//	Menu::loadSprites();
	float pionowyMargines,poziomyMargines;
	pionowyMargines = 80;
	poziomyMargines = 130;
	float imgWidth,imgHeight,temp;
	imgWidth=3774.0f;
	imgHeight=447.0f;
	//TODO: Sprawdzić czy dziala dla wielu rozdzielczosci
//	temp = (1366.0f-2*pionowyMargines)*imgHeight/imgWidth;
	temp = (1366.0f-2*pionowyMargines)*imgHeight/imgWidth;
//	Sprite *title = new Sprite((-1366.0f/2)+pionowyMargines,1366.0f/2-poziomyMargines-temp,1366.0f-2*pionowyMargines,temp,"../src/img/title.png");
	Sprite *title = new Sprite((-1366.0f/2)+pionowyMargines,768.0f/2-poziomyMargines-temp,1366.0f-2*pionowyMargines,temp,"../src/img/title.png");
	this->listaSpritowFG.push_back(title);
}


void MainMenu::loadCallBacks() {
	this->callBackArray.push_back(singlePlayer);
	this->callBackArray.push_back(multiPlayer);
	this->callBackArray.push_back(options);
	this->callBackArray.push_back(exitWindow);

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
	//TODO: Sprawdzić czy dziala dla wielu rozdzielczosci
	float lewyMargines = (-1366.0f/2)+80;
//	float lewyMargines = (-1366.0f/2)+80;
    float yFirstButton = -90;
    float distance = 15;
    for (unsigned int i = 0; i<this->listaWspolrzednych.size();i++){
        float temp=0;
//        if(i!=0){
            temp = temp + i*distance;
            for(unsigned int j=1;j<=i ;j++){
                temp = temp + listaWspolrzednych[j].w;
            }
//        }
        float y = yFirstButton - temp;
        this->listaPrzesuniec.push_back(glm::vec3(lewyMargines,y,0));

    }
}

void singlePlayer(Button *button, GLFWwindow *window, GLFWcursor *cursor) {
	std::cout << "Single Player!" << std::endl;
	inputActions::getInstance().changeState('s',window,cursor);
//	inputActions::getInstance().changeGame(window, cursor);
}
void multiPlayer(Button *button, GLFWwindow *window, GLFWcursor *cursor) {
	std::cout << "MultiPlayer!" << std::endl;
}

void options(Button *button, GLFWwindow *window, GLFWcursor *cursor) {
	// this->callBackArray.push_back(static_cast(MainMenu::singlePlayer));
//	OptionMenu *optionMenu = new OptionMenu(state,window,cursor);
	inputActions::getInstance().changeState('o',window,cursor);
	std::cout << "Options!" << std::endl;

}

void exitWindow(Button *button, GLFWwindow *window, GLFWcursor *cursor) {
	std::cout << "Exit window!" << std::endl;
	glfwSetWindowShouldClose(window, GL_TRUE);

}
