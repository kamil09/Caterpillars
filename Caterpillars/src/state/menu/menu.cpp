#include "menu.hpp"
#include "../../inputActions.hpp"


Menu::Menu(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
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
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFunc (GL_ONE, GL_ONE);
    this->background->draw2();
    for(i=0;i<this->buttonCount;i++){
        listaButtonow[i]->draw2();

    }
    glDisable(GL_BLEND);
}

void Menu::pressESC(){
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Menu::releaseLMB(){
    // this->readPixel(this->window);
    this->checkButtons();
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
    this->background = new Button(0,0.0f,0.0f,0.0f,2.0f,2.0f,texturePath,NULL);
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
        // this->callBackArray[i];
        // Button *nowyButton = new Button(this->buttonCount,x,baseY,0.0f,this->buttonWidth,this->buttonHeight,this->listaTekstur[this->buttonCount-1],this->callBackArray[i]);
        Button *nowyButton = new Button(this->buttonCount,x,baseY,0.0f,this->buttonWidth,this->buttonHeight,this->listaTekstur[this->buttonCount-1],this->callBackArray[i]);
        std::cout << "X: " << x << " Y: " << baseY << std::endl;
        this->listaButtonow.push_back(nowyButton);
    }
}



void Menu::checkCursor(){
    float *data = this->readPixel(this->window);
    inputActions::getInstance().pixelData = data;
    // std::cout << "Obecne data[0]: " << data[0] << std::endl;
    if(data[0]==0.0f && data[1] == 0.0f && data[2] == 0.0f){
        inputActions::getInstance().changeCursor(GLFW_CROSSHAIR_CURSOR);
    }
    else{
        inputActions::getInstance().changeCursor(GLFW_HAND_CURSOR);
    }
}

void Menu::checkButtons(){
    float *data = inputActions::getInstance().pixelData;
    int i;
    // std::cout << "kliknoles!" << std::endl;

    int wybRed = data[0]*1000000;
    int wybGreen = data[1]*1000000;
    int wybBlue = data[2]*1000000;

    for(i=0;i<buttonCount;i++){
        // std::cout << "kolory: r = " << this->listaButtonow[i]->r << " g = " << this->listaButtonow[i]->g << " b = " << this->listaButtonow[i]->b << std::endl;
        // std::cout << "Wybrano!!!!!!!: r = " << round(data[0]) << " g = " << data[1] << " b = " << data[2] << std::endl;
        // std::cout << "Wybrano!!!!!!!: r = " << round(data[0]) << " g = " << round(data[1]) << " b = " << round(data[2]) << std::endl;

        int tempRed = this->listaButtonow[i]->r*1000000;
        int tempGreen = this->listaButtonow[i]->g*1000000;
        int tempBlue = this->listaButtonow[i]->b*1000000;
        // std::cout << "kolor!!!!!!!!!: r = " << tempRed << " g = " << tempGreen << " b = " << tempBlue << std::endl;
        // if(this->listaButtonow[i]->r == data[0] && this->listaButtonow[i]->g == data[1] && this->listaButtonow[i]->b == data[2]){
        if(tempRed == wybRed && tempGreen == wybGreen && tempBlue == wybBlue){
        // if(this->listaButtonow[i]->r == data[0]){
            // if(this->listaButtonow[i]->g == data[1]){
                // if(this->listaButtonow[i]->b == data[2]){
                    std::cout << "Wybraleś przycisk numer: " << i << std::endl;
                    this->listaButtonow[i]->callBackFunction(this->window,this->cursor);
                    // this->listaButtonow[i]->select();
                    // inputActions::getInstance().nextState = static_cast<gameCaseType>(i+1);
                    // inputActions::getInstance().changeState = true;
                // }
            // }
        }
    }
}
