//
// Created by lewin on 06.07.16.
//

#include "subMenu.hpp"
#include "../../../inputActions.hpp"


SubMenu::SubMenu(State *state, GLFWwindow *window, GLFWcursor *cur) : Menu(window, cur) {
    this->primaryState = state;
    this->createBackgroud("");
}


void goBack(Button *state, GLFWwindow *window, GLFWcursor *cursor) {
//    state->keysControl();
//    inputActions::getInstance().changeState('m',window,cursor);
    SubMenu* now =(SubMenu*)inputActions::getInstance().currentState;
    inputActions::getInstance().currentState=now->primaryState;
}



void SubMenu::draw() {
    if(this->check!=0){
        this->primaryState->draw();
    }
    Menu::draw();
//    if(this->check!=0){
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//        for (int i = 0; i < this->primaryState->buttonCount; i++) {
//
//        }
//
//        for(unsigned int i=0; i<this->primaryState->listaSpritowFG.size();i++){
//            this->primaryState->listaSpritowFG[i]->draw();
//        }
//
//        glDisable(GL_BLEND);
//    }
}


void SubMenu::pressESC() {
//    State::pressESC();
    inputActions::getInstance().currentState = this->primaryState;
}

void goExit(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    inputActions::getInstance().changeState('m',window,cursor);
}