#include "menu.hpp"
#include "../../inputActions.hpp"


Menu::Menu(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
    std::cout << "Tworzenie menu!" << std::endl;
    this->customPollEvents = true;
    this->buttonCount = 0;
    this->check = 0;
    // this->createButtons(4);


    // this->font = new Font("../src/fonts/Coalition.ttf",window,48);

}

void Menu::run(){
    // std::cout << "Rysowanie" << std::endl;
    this->check=0;
    this->draw();
    this->checkCursor();
    glfwPollEvents();
    this->check=1;
    this->draw();
    errorCheck("RYSOWANIE MENU");
}

void Menu::draw(){
    int i;
    if(this->check!=0){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        this->background->check=this->check;
        this->background->draw();
    }

    for(i=0;i<this->buttonCount;i++){
        listaButtonow[i]->check=this->check;
        listaButtonow[i]->draw();
//        std::cout << "draw" << std::endl;
    }
//    std::cout << "#poczatek draw" << std::endl;
    if(this->check!=0){
        for(unsigned int i=0; i<this->listaSpritow.size();i++){
            this->listaSpritow[i]->draw();
        }
        glDisable(GL_BLEND);
    }
    else{
        this->background->check=this->check;
        this->background->draw();
    }
}


void Menu::pressESC(){
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Menu::releaseLMB(){
    // this->readPixel(this->window);
//    this->checkButtons();
    if(this->currentButton!=-1){
        this->listaButtonow[this->currentButton]->callBackFunction(this->window,this->cursor);
    }
}

float* Menu::readPixel(GLFWwindow *window){
	glFlush();
	glFinish();
	// glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// float data[4];
	float *data = (float*) malloc(sizeof(float)*4);
	inputActions::getInstance().getMouseCurrentPosition(window);
	glReadPixels(inputActions::getInstance().getCursorLastX(),viewport[3]-1-inputActions::getInstance().getCursorLastY(),1,1, GL_RGBA, GL_FLOAT, data);
	glFlush();
	glFinish();
	// std::cout << "red: " << data[0] << " green: " << data[1] << " blue: " << data[2] << " alpha: " << data[3] << std::endl;
    return data;
}

void Menu::createBackgroud(GLchar *fileName){
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    this->background = new Button(0,(float)-viewport[2]/2.0f,(float)-viewport[3]/2.0f,(float)viewport[2],(float)viewport[3],fileName,NULL);
}


void Menu::createButtons() {
    std::cout << "tworzenie buttonow: " << std::endl;
    for(unsigned int i=0;i < this->listaWspolrzednych.size();i++){
        this->buttonCount++;
        glm::vec4 pozycja = this->listaWspolrzednych[this->buttonCount-1];
        std::cout << "pozycja: " << pozycja.w << std::endl;
        char *temp = new char[this->listaTekstur[this->buttonCount-1].size() + 1];
        strcpy(temp,this->listaTekstur[this->buttonCount-1].c_str());
        Button *nowyButton = new Button(this->buttonCount,pozycja.x,pozycja.y,pozycja.z,pozycja.w,temp,this->callBackArray[this->buttonCount-1]);
        glm::vec3 translate = this->listaPrzesuniec[i];
        nowyButton->setTraM(translate.x,translate.y,translate.z);
        nowyButton->alpha=0.5f;
        this->listaButtonow.push_back(nowyButton);
    }
    std::cout << "button width: " << this->listaButtonow[0]->size.x << std::endl;
}



void Menu::checkCursor(){
    float *data = this->readPixel(this->window);
    inputActions::getInstance().pixelData = data;
    int test = this->checkButtons();
    if(this->currentButton!=test){
        if(this->currentButton!=-1){
            this->listaButtonow[this->currentButton]->alpha=0.5f;
        }
        this->currentButton = test;
        if(this->currentButton!=-1){
            this->listaButtonow[this->currentButton]->alpha=1.0f;
            inputActions::getInstance().changeCursor(GLFW_HAND_CURSOR);
        }
        else{
            inputActions::getInstance().changeCursor(GLFW_CROSSHAIR_CURSOR);
        }
    }
}

int Menu::checkButtons(){
    float *data = inputActions::getInstance().pixelData;
    int i;
    // std::cout << "kliknoles!" << std::endl;

    int wybRed = data[0]*1000000;
    int wybGreen = data[1]*1000000;
    int wybBlue = data[2]*1000000;

    for(i=0;i<buttonCount;i++){
        int tempRed = this->listaButtonow[i]->r*1000000;
        int tempGreen = this->listaButtonow[i]->g*1000000;
        int tempBlue = this->listaButtonow[i]->b*1000000;
        if(tempRed == wybRed && tempGreen == wybGreen && tempBlue == wybBlue){
//            std::cout << "Wybraleś przycisk numer: " << i << std::endl;
            return i;
//            this->listaButtonow[i]->callBackFunction(this->window,this->cursor);
        }
    }
    return -1;
}
