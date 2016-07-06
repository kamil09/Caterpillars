//
// Created by lewin on 06.07.16.
//

#include "subMenu.hpp"
#include "../../../inputActions.hpp"


SubMenu::SubMenu(Menu *menu, GLFWwindow *window, GLFWcursor *cur) : Menu(window,cur) {
    this->primaryMenu = menu;
    this->createBackgroud(NULL);
}


void goBack(State *state, GLFWwindow *window, GLFWcursor *cursor) {
//    state->buttonControl();
    inputActions::getInstance().changeState('m',window,cursor);
}


void SubMenu::buttonControl() {

}


void SubMenu::draw() {
    if(this->check!=0){
        this->primaryMenu->draw();
    }
    Menu::draw();
//    if(this->check!=0){
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//        for (int i = 0; i < this->primaryMenu->buttonCount; i++) {
//
//        }
//
//        for(unsigned int i=0; i<this->primaryMenu->listaSpritowFG.size();i++){
//            this->primaryMenu->listaSpritowFG[i]->draw();
//        }
//
//        glDisable(GL_BLEND);
//    }
}


