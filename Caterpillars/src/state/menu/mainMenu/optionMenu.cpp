//
// Created by lewin on 06.07.16.
//

#include "optionMenu.hpp"


OptionMenu::OptionMenu(State *state, GLFWwindow *window, GLFWcursor *cur) : SubMenu(state, window, cur) {
    this->loadSprites();
    this->loadCallBacks();
    this->loadTextureFiles();
    this->loadCoordinates();
    this->loadTranslates();
    this->createButtons();
}


void OptionMenu::loadTextureFiles() {
    this->listaTekstur.push_back("../src/img/back.png");
//    Menu::loadTextureFiles();
}

void OptionMenu::loadCoordinates() {
    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
//    Menu::loadCoordinates();
}

void OptionMenu::loadTranslates() {
    float poziomyMargines, pionowyMargines;
    poziomyMargines = 20;
    pionowyMargines = 30;
    //TODO: sprawdzic czy dziala dla wszystkich rozdzielczosci
    this->listaPrzesuniec.push_back(glm::vec3(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,0.8f));
//    this->listaPrzesuniec.push_back(glm::vec3(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,0.8f));

//    Menu::loadTranslates();
}



void OptionMenu::loadCallBacks() {
//    Menu::loadCallBacks();
    this->callBackArray.push_back(goBack);
}


void OptionMenu::loadSprites() {
    float poziomyMargines, pionowyMargines;
    poziomyMargines = 80;
    pionowyMargines = 80;
    Sprite *ramka = new Sprite(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,1366.0f/2+2*pionowyMargines,768.0f/2+2*poziomyMargines,"../src/img/ramka.png");
    float x,y,z;
    x= y =0.0f;
    z = 1.0f;
    ramka->setTraM(x,y,z);
    Sprite *tlo = new Sprite(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,1366.0f/2+2*pionowyMargines,768.0f/2+2*poziomyMargines,"../src/img/tlo.png");
    tlo->setTraM(x,y,0.2f);
    this->settingsPrint(tlo);
    this->listaSpritowBG.push_back(tlo);
    this->listaSpritowFG.push_back(ramka);
//    Menu::loadSprites();

}


void OptionMenu::settingsPrint(Sprite *sprite) {
    this->readSettings();
//    sprite->initFont("../src/fonts/NotoSansCJK-Black.ttc",14);
    sprite->initFont("../src/fonts/Coalition.ttf",14);
    float poziomyMargines, pionowyMargines,distance;
    poziomyMargines = 100;
    pionowyMargines = 40;
    distance = 10.0f;
    for (unsigned int i = 0; i < this->ustawieniaTeksty.size(); ++i) {
        float y=0;
        if (i==0){
            y = poziomyMargines;
            sprite->addTextL(this->ustawieniaTeksty[i],pionowyMargines,y,1.0f,glm::vec3(1.0f,1.0f,1.0f));
        }
        else{
            std::cout << "wysokosc: " << sprite->font->height(1.0f) << std::endl;
            y = sprite->teksty[i-1]->y + sprite->font->height(1.0f) + distance;
            sprite->addText(this->ustawieniaTeksty[i],sprite->teksty[i-1]->x,y,1.0f,glm::vec3(1.0f,1.0f,1.0f));
        }
        std::cout << "odleglosc y: " << y << std::endl;
        std::cout << "Setting: " << this->ustawieniaTeksty[i] << std::endl;
    }
}


void OptionMenu::readSettings() {
//    Setting setting = Setting::getInstance();
    std::string temp;
    temp = "Game settings can be changed by configuring settings file";
    this->ustawieniaTeksty.push_back(temp);
    this->ustawieniaTeksty.push_back("");
    temp = "Full window: " + this->checkBool(Setting::getInstance().getFullWindow());
    this->ustawieniaTeksty.push_back(temp);
    temp = "Full resolution: " + this->checkBool(Setting::getInstance().getFullResolution());
    this->ustawieniaTeksty.push_back(temp);
    temp = "If full resolution is disabled then the resolution below is used:";
    this->ustawieniaTeksty.push_back(temp);
    temp = "Width: " + to_string(Setting::getInstance().getWidth());
    this->ustawieniaTeksty.push_back(temp);
    temp = "Height: " + to_string(Setting::getInstance().getHeight());
    this->ustawieniaTeksty.push_back(temp);
    temp = "Difficulty: " + to_string(Setting::getInstance().getDifficulty());
    this->ustawieniaTeksty.push_back(temp);
    temp = "Music: " + this->checkBool(Setting::getInstance().getMusic());
    this->ustawieniaTeksty.push_back(temp);
    temp = "Sounds: " + this->checkBool(Setting::getInstance().getSounds());
    this->ustawieniaTeksty.push_back(temp);
    std::string str(Setting::getInstance().getRankFileName());
    temp = "Rank file name: " + str;
    this->ustawieniaTeksty.push_back(temp);
}


std::string OptionMenu::checkBool(bool doTestu) {
    if(doTestu == true){
        return "Yes";
    }
    else{
        return "No";
    }
}
