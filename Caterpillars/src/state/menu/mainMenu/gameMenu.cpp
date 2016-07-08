//
// Created by lewin on 07.07.16.
//

#include "gameMenu.hpp"
#include "../../../inputActions.hpp"

GameMenu::GameMenu(State *state, GLFWwindow *window, GLFWcursor *cur) : SubMenu(state,window,cur) {
    this->loadSprites();
    this->loadCallBacks();
    this->loadTextureFiles();
    this->loadCoordinates();
    this->loadTranslates();
    this->createButtons();
    this->font = new Font("../src/fonts/Coalition.ttf",17);
    std::vector<glm::vec3> kolory;
    kolory ={
            glm::vec3(0.612, 0, 0),
    };
    std::vector<std::string> nazwy;
    nazwy = {
            "Player 1"
    };
    int caterpillars = 1;
    float pionowyMargines,poziomyMargines,y;
    pionowyMargines = 10.0f;
    poziomyMargines = -10.0f;
    float temp = (60.0f/2000.0f)*this->listaSpritowFG[0]->size.y/2;
//    (this->listaButtonow[0]->pos.y - this->listaSpritowBG[0]->pos.y-temp)
    y = (this->listaSpritowBG[0]->size.y -((this->listaButtonow[0]->pos.y/2 - this->listaSpritowBG[0]->pos.y/2 - temp)+this->listaButtonow[0]->size.y)-poziomyMargines)/4.0f;
    Sprite *blok = new Sprite(this->listaSpritowBG[0]->pos.x + pionowyMargines,-y/2,this->listaSpritowBG[0]->size.x - 2*pionowyMargines,y,glm::vec4(kolory[0],1.0f));
    blok->setTraM(0.0f,this->listaSpritowBG[0]->size.y/2-blok->size.y/2-temp-20.0f,0.5f);
    blok->font = this->font;
//    blok->addTextM(nazwy[0],-blok->size.x/2+this->font->length(nazwy[0],1.0f)/2.0+2*pionowyMargines,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
    std::string tekst = nazwy[0] + " - Caterpillars: " + to_string(caterpillars);
//    blok->addTextM(tekst,blok->pos.x+this->font->length(tekst,1.0f)/2.0+2*pionowyMargines+40.0f,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
    blok->addTextLM(tekst,40.0f,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));

//    blok->addText("Catterpillars: " + to_string(caterpillars),blok->teksty[0]->x,blok->teksty[0]->y,1.0f,glm::vec3(1.0f,1.0f,1.0f));
    this->listaSpritowBG.push_back(blok);
}


void GameMenu::loadTextureFiles() {
    this->listaTekstur.push_back("../src/img/back.png");
    this->listaTekstur.push_back("../src/img/start.png");
//    Menu::loadTextureFiles();
}

void GameMenu::loadCoordinates() {
    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
//    this->listaWspolrzednych.push_back(glm::vec4());
//    Menu::loadCoordinates();
}

void GameMenu::loadTranslates() {
    float poziomyMargines, pionowyMargines;
    poziomyMargines = -20;
    pionowyMargines = -35;
    this->listaPrzesuniec.push_back(glm::vec3(-this->windowXsize/4+pionowyMargines,-this->windowYsize/4+poziomyMargines,0.8f));
    this->listaPrzesuniec.push_back(glm::vec3(this->windowXsize/4-pionowyMargines-this->listaWspolrzednych[1].z,-this->windowYsize/4+poziomyMargines,0.8f));

//    Menu::loadTranslates();
}

void GameMenu::loadCallBacks() {
    this->callBackArray.push_back(goBack);
    this->callBackArray.push_back(goStart);
//    Menu::loadCallBacks();
}


void GameMenu::loadSprites() {
//    Menu::loadSprites();
    float poziomyMargines, pionowyMargines;
    poziomyMargines = 80;
    pionowyMargines = 80;
    Sprite *ramka = new Sprite(-this->windowXsize/4-pionowyMargines,-this->windowYsize/4-poziomyMargines,this->windowXsize/2+2*pionowyMargines,this->windowYsize/2+2*poziomyMargines,"../src/img/ramka.png");
//    Sprite *ramka = new Sprite(0,0,this->windowXsize/2+2*pionowyMargines,this->windowYsize/2+2*poziomyMargines,"../src/img/ramka.png");
    float x,y,z;
//    x= -this->windowXsize/4-pionowyMargines;
//    y =-this->windowYsize/4-poziomyMargines;
//    z = 1.0f;
    x = y = 0.0f;
    ramka->setTraM(x,y,1.0f);
//    Sprite *tlo = new Sprite(-this->windowXsize/4-pionowyMargines,-this->windowYsize/4-poziomyMargines,this->windowXsize/2+2*pionowyMargines,this->windowYsize/2+2*poziomyMargines,"../src/img/tlo.png");
    Sprite *tlo = new Sprite(ramka->pos.x,ramka->pos.y,ramka->size.x,ramka->size.y,"../src/img/tlo.png");
    tlo->setTraM(x,y,0.2f);
    this->listaSpritowBG.push_back(tlo);
    this->listaSpritowFG.push_back(ramka);
//    Menu::loadSprites();


}


void goStart(State *state, GLFWwindow *window, GLFWcursor *cursor) {
    inputActions::getInstance().changeState('g',window,cursor);
}

