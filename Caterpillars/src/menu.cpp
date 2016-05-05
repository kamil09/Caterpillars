#include "menu.hpp"
#include "inputActions.hpp"


Menu::Menu(GLFWwindow *window) : State(window){
    std::cout << "Tworzenie menu!" << std::endl;
    this->buttonCount = 0;
    this->createButtons(4);
}

void Menu::run(){
    this->draw();
}

void Menu::draw(){
    int i;
    for(i=0;i<this->buttonCount;i++){
        listaButtonow[i]->rysuj();
    }
}

void Menu::pressESC(){
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Menu::releaseLMB(){
    this->readPixel(this->window);
}

void Menu::readPixel(GLFWwindow *window){
	glFlush();
	glFinish();
	// glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float data[4];
	inputActions::getInstance().getMouseCurrentPosition(window);
	glReadPixels(inputActions::getInstance().getCursorLastX(),viewport[3]-1-inputActions::getInstance().getCursorLastY(),1,1, GL_RGBA, GL_FLOAT, data);
	glFlush();
	glFinish();
	std::cout << "red: " << data[0] << " green: " << data[1] << " blue: " << data[2] << " alpha: " << data[3] << std::endl;
}

void Menu::createButtons(int count){
    for(int i=0; i<count; i++){
        this->buttonCount++;
		Button *nowyButton = new Button(255 + (i*200),0.0f,0.60f-(i*0.4f),0.5f,0.3f);
        this->listaButtonow.push_back(nowyButton);
    }
}
