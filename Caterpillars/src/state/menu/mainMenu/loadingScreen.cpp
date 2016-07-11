//
// Created by lewin on 09.07.16.
//

#include "loadingScreen.hpp"
#include "../../../inputActions.hpp"


//LoadingScreen::LoadingScreen(GLFWwindow *window, GLFWcursor *cur) : Menu(window,cur) {
//    Sprite *background = new Sprite(-1366.0f/2.0f,-768.0f/2.0f,1366.0f,768.0f,glm::vec4(0.067f, 0.047f, 0.047f,1.0f));
//    background->initFont("../src/fonts/Coalition.ttf",30);
//    background->addTextM("Please wait - Loading Map...",0.0f,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
//    this->listaSpritowBG.push_back(background);
//}


LoadingScreen::LoadingScreen(State *state, GLFWwindow *window, GLFWcursor *cur) : SubMenu(state,window,cur) {
    Sprite *loading = new Sprite(-1366.0f/2.0f,-768.0f/2.0f,1366.0f,768.0f,glm::vec4(0.067f, 0.047f, 0.047f,0.75f));
    loading->setTraM(0.0f,0.0f,0.9f);
    loading->initFont("../src/fonts/Coalition.ttf",30);
    loading->addTextM("Please wait - Loading Map...",0.0f,-30.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
    this->listaSpritowFG.push_back(loading);
    this->czyTworzyc = false;
}


void LoadingScreen::run() {
    Menu::run();
    if(this->czyTworzyc){
         inputActions::getInstance().changeState('g',this->window,this->cursor);
    }
    else{
        this->czyTworzyc = true;
    }
}

