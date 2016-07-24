//
// Created by lewin on 23.07.16.
//

#include "endMenu.hpp"
#include "../../inputActions.hpp"


EndMenu::EndMenu(State *state, GLFWwindow *window, GLFWcursor *cur) : SubMenu(state,window,cur) {
    this->font = new Font("../src/fonts/Coalition.ttf",60);
    this->loadSprites();
    this->loadCallBacks();
    this->loadTextureFiles();
    this->loadCoordinates();
    this->loadTranslates();
    this->createButtons();
}


void EndMenu::loadCallBacks() {
//    this->callBackArray.push_back(goBack2);
    this->callBackArray.push_back(goExit);
}

void EndMenu::loadTextureFiles() {
//    this->listaTekstur.push_back("../src/img/back.png");
    this->listaTekstur.push_back("../src/img/exit2.png");
}

void EndMenu::loadCoordinates() {
//    this->listaWspolrzednych.push_back(glm::vec4(0,0,189.8686311322,59.078289839));
//    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
}

void EndMenu::loadTranslates() {
    float distance= 70.0f;
    //TODO: Sprawdzic czy dziala na wszystkich rozdzielczosciach
    float y = 0.0f;
    for (unsigned int i = 0; i < this->listaSpritowBG[0]->teksty.size(); ++i) {
        y -= this->listaSpritowBG[0]->font->height(1.0f);
    }
    y -= this->listaWspolrzednych[0].w + 10.0f;
    this->listaPrzesuniec.push_back(glm::vec3(-this->listaWspolrzednych[0].z/2.0f,y + 20.0f,0.8f));
//    this->listaPrzesuniec.push_back(glm::vec3(0.0f+distance,y,0.8f));
}

void EndMenu::loadSprites() {
    Sprite *tlo = new Sprite(-1366.0f/2.0f,-768.0f/2.0f,1366.0f,768.0f,glm::vec4(0.067f, 0.047f, 0.047f,0.7f));
    tlo->setTraM(0.0f,0.0f,0.2f);
    tlo->font = this->font;
    std::string text = inputActions::getInstance().winner->nazwa + " Wins!";
    tlo->addTextM(text,0.0f,-40.0f,1.0f,inputActions::getInstance().winner->kolor);
    this->listaSpritowBG.push_back(tlo);
}

void EndMenu::pressESC() {
//    SubMenu::pressESC();
}
