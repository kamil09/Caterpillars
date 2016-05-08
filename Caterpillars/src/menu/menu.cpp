#include "menu.hpp"
#include "../inputActions.hpp"


Menu::Menu(GLFWwindow *window) : State(window){
    std::cout << "Tworzenie menu!" << std::endl;
    this->customPollEvents = true;
    this->buttonCount = 0;
    // this->createButtons(4);
}

void Menu::run(){
    // std::cout << "Rysowanie" << std::endl;
    this->draw();
    this->checkCursor();
    glfwPollEvents();
    this->draw2();
    // errorCheck("Cos jest nie tak");
}

void Menu::draw(){
    int i;
    for(i=0;i<this->buttonCount;i++){
        listaButtonow[i]->draw();
    }
    this->background->draw();
}

void Menu::draw2(){
    int i;
    for(i=0;i<this->buttonCount;i++){
        listaButtonow[i]->draw2();

    }
    this->background->draw2();
}

void Menu::pressESC(){
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Menu::releaseLMB(){
    this->readPixel(this->window);
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

void Menu::createBackgroud(const char* texturePath){
    this->background = new Button(0,0,0,2.0f,2.0f,texturePath);
}

void Menu::createButtons(int count,GLfloat x,GLfloat y){
    // std::cout << "WTF: " << this->buttonHeight << " " << this->buttonDistance << std::endl;
    for(int i=0; i<count; i++){
        this->buttonCount++;
        GLfloat baseY;
        // if(i==0){
        //     baseY = y;
        // }
        // else{
            baseY = y - i*(this->buttonHeight/2 + this->buttonDistance);
        // }
		// Button *nowyButton = new Button(255 + (i*200),0.0f,0.60f-(i*0.4f),0.5f,0.3f);
        Button *nowyButton = new Button(this->buttonCount*255,x,baseY,this->buttonWidth,this->buttonHeight,this->listaTekstur[this->buttonCount-1]);
        std::cout << "X: " << x << " Y: " << baseY << std::endl;
        this->listaButtonow.push_back(nowyButton);
    }
}

void Menu::loadTextureFiles(){
    // this->listaTekstur.resize(this->listaTekstur.size()+4);
    // std::string temp = "../src/img/menuLab1.png";
    // this->listaTekstur[0] = std::string("../src/img/menuLab1.png");
    this->listaTekstur[0] = "../src/img/menuLab1.png";
    this->listaTekstur[1] = "../src/img/menuLab2.png";
    this->listaTekstur[2] = "../src/img/menuLab3.png";
    this->listaTekstur[3] = "../src/img/menuLab4.png";

    // this->listaTekstur.pop_back("../src/img/m    enuLab2.png");
    // this->listaTekstur.pop_back("../src/img/menuLab3.png");
    // this->listaTekstur.pop_back("../src/img/menuLab4.png");
}

void Menu::checkCursor(){
    float *data = this->readPixel(this->window);
    // std::cout << "Obecne data[0]: " << data[0] << std::endl;
    if(data[0]==0.0f){
        GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
        glfwSetCursor(this->window, cursor);
    }
    else{
        GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
        glfwSetCursor(this->window, cursor);
    }
}
