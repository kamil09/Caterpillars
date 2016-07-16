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
    this->createBlocks();
}


void GameMenu::createBlocks() {
    int fontSize = 17;
    this->font = new Font("../src/fonts/Coalition.ttf",fontSize);
//    std::vector<glm::vec3> kolory;
//    kolory ={
//            glm::vec3(0.612, 0, 0),
//    };
//    std::vector<std::string> nazwy;
//    nazwy = {
//            "Player 1"
//    };
//    int caterpillars = 1;
    float pionowyMargines,poziomyMargines;
    pionowyMargines = 10.0f;
    poziomyMargines = -10.0f;
    float temp = (60.0f/2000.0f)*this->listaSpritowFG[0]->size.y/2;
    this->blockHeight = (this->listaSpritowBG[0]->size.y -((this->listaButtonow[0]->pos.y/2 - this->listaSpritowBG[0]->pos.y/2 - temp)+this->listaButtonow[0]->size.y)-poziomyMargines)/4.0f;


//    back->addTextM(nazwy[0],-back->size.x/2+this->font->length(nazwy[0],1.0f)/2.0+2*pionowyMargines,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
//    back->addTextM(tekst,back->pos.x+this->font->length(tekst,1.0f)/2.0+2*pionowyMargines+40.0f,0.0f,1.0f,glm::vec3(1.0f,1.0f,1.0f));
//    std::cout << "Tworzenie plusa" << std::endl;
//    Button *plus = new Button(this->buttonCount,0.0f,0.0f,25.0f,25.0f,"../src/img/plus.png",increase);
//    plus->setTraM(back->teksty[0]->x+this->font->length(tekst,1.0f)+1,0.0f,0.8f);
//    plus->setTraM(back->teksty[0]->x , back->teksty[0]->y,0.8f);
    int playerCount = Setting::getInstance().players.size();
    int tempCount = this->buttonCount;
    this->blocks.resize(playerCount);
//    this->blocks.resize(1);

    this->moveY = this->listaSpritowBG[0]->size.y/2-this->blockHeight/2-temp-20.0f;
    for (int i = 0; i < playerCount; i++) {
//    for (int i = 0; i < 1; i++) {
//        player newPlayer;
        this->blocks[i].playerNumber=i;
//        std::cout << Setting::getInstance().players[i].kolor.x << std::endl;
        //Tworzenie tla i napisu
        Sprite *back = new Sprite(this->listaSpritowBG[0]->pos.x + pionowyMargines, -this->blockHeight / 2,
                                  this->listaSpritowBG[0]->size.x - 2 * pionowyMargines, this->blockHeight, glm::vec4(Setting::getInstance().players[i].kolor,1.0f));
        back->font = this->font;
        this->blocks[i].back=back;
//        float moveY = this->listaSpritowBG[0]->size.y/2-back->size.y/2-temp-20.0f;
        std::string tekst = Setting::getInstance().players[i].nazwa + " - Caterpillars: " + to_string(Setting::getInstance().players[i].caterpillarsCount);
//        back->setTraM(0.0f,this->moveY,0.4f);
//        back->addTextLM(tekst, 40.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        //PLUS
        tempCount++;
        Button *plus = new Button(tempCount, 0.0f, 0.0f, 25.0f, 25.0f, "../src/img/plus.png", increase);
        plus->binds = i;
        this->blocks[i].plus = plus;
//        plus->setTraM(back->teksty[0]->x + this->font->length(back->teksty[0]->text, 1.0f) + 15, this->moveY, 0.8f);
        plus->kolor.a = 0.6f;
        //MINUS
        tempCount++;
        Button *minus = new Button(tempCount, 0.0f, 0.0f, 25.0f, 25.0f, "../src/img/minus.png", decrease);
        minus->binds = i;
        this->blocks[i].minus=minus;
//        minus->setTraM(back->teksty[0]->x + this->font->length(back->teksty[0]->text, 1.0f) + 15, moveY - 25.0f, 0.8f);
        minus->kolor.a = 0.6f;
//    back->addText("Catterpillars: " + to_string(caterpillars),back->teksty[0]->x,back->teksty[0]->y,1.0f,glm::vec3(1.0f,1.0f,1.0f));
//        this->listaButtonow.push_back(plus);
//        this->listaButtonow.push_back(minus);
//        this->listaSpritowBG.push_back(back);
//        this->blocks[i].czyRysowac = true;
//        if(i==0 || i ==3){
//            this->kolejnosc.push_back(i);
//        }
//        this->kolejnosc.push_back(i);
        tempCount++;
        Button *del = new Button(tempCount,(float)-this->blockHeight -40.0f,-back->size.y/2.0f,(float)2.0f*this->blockHeight+80.0f,(float)back->size.y,"../src/img/delete.png",deletePlayer);
        del->font = this->font;
        del->addTextM("Delete Player",0.0f,0.0f,1.0f,glm::vec3(0.712, 0, 0));
        del->binds = i;
        del->kolor.a = 0.6f;
        this->blocks[i].del=del;
    }
    tempCount++;

    this->buttonAdd = new Button(tempCount, this->listaSpritowBG[0]->pos.x + pionowyMargines, -this->blockHeight / 2,
                                 this->listaSpritowBG[0]->size.x - 2 * pionowyMargines, this->blockHeight,
                                 "../src/img/add.png", addPlayer);
    this->buttonAdd->kolor.a = 0.6f;
//    this->buttonAdd->font = this->font;
    this->buttonAdd->initFont("../src/fonts/Coalition.ttf",fontSize*2-5);
    this->buttonAdd->addTextM("+ Add new player",0.0f,0.0f,1.0f,glm::vec3(0.412, 0.941, 0.067));
}




void GameMenu::run() {
    for (int j = 0; j < Setting::getInstance().players.size(); ++j) {
        if(Setting::getInstance().players[j].czyGra){
            std::vector<int>::iterator it = std::find(this->kolejnosc.begin(),this->kolejnosc.end(),j);
            if(it == this->kolejnosc.end()){
                this->kolejnosc.push_back(j);
            }
        }
        else{
            std::vector<int>::iterator it = std::find(this->kolejnosc.begin(),this->kolejnosc.end(),j);
            if(it != this->kolejnosc.end()){
                this->kolejnosc.erase(it);
            }
        }
    }
    int k;
    for (k= 0; k < this->kolejnosc.size(); ++k) {
        int obecny = this->kolejnosc[k];
//        if(this->blocks[i].czyRysowac){
//            std::cout << "Rysuje" << std::endl;
        float positionY = this->moveY - k*this->blockHeight;
        this->blocks[obecny].back->setTraM(0.0f,positionY,0.4f);
//        std::string tekst = Setting::getInstance().players[i].nazwa + " - Caterpillars: " + to_string(Setting::getInstance().players[i].caterpillarsCount);
        std::string tekst = Setting::getInstance().players[obecny].nazwa + " - Caterpillars: ";
        if(!this->blocks[obecny].back->teksty.empty()){
            this->blocks[obecny].back->teksty.clear();
        }
        this->blocks[obecny].back->addTextLM(tekst, 90.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        float dlugosc = this->blocks[obecny].back->teksty[0]->x + this->font->length(this->blocks[obecny].back->teksty[0]->text, 1.0f);
//        std::cout << "dlugosc: " << dlugosc << std::endl;
//        if(this->blocks[obecny].plus->posM[3][0] == 0.0f||dlugosc > this->blocks[obecny].plus->posM[3][0]){
        dlugosc += 15.0f;
//            this->blocks[obecny].plus->setTraM(this->blocks[obecny].back->teksty[0]->x + this->font->length(this->blocks[obecny].back->teksty[0]->text, 1.0f) + 15, positionY , 0.8f);
//            this->blocks[obecny].minus->setTraM(this->blocks[obecny].back->teksty[0]->x + this->font->length(this->blocks[obecny].back->teksty[0]->text, 1.0f) + 15, positionY- this->blocks[obecny].minus->size.y, 0.8f);
            this->blocks[obecny].plus->setTraM(dlugosc, positionY , 0.8f);
            this->blocks[obecny].minus->setTraM(dlugosc, positionY- this->blocks[obecny].minus->size.y, 0.8f);
        this->blocks[obecny].back->addText(to_string(Setting::getInstance().players[obecny].caterpillarsCount), dlugosc + this->blocks[obecny].plus->size.x + 10.0f, this->blocks[obecny].back->teksty[0]->y, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//        }
        this->blocks[obecny].del->setTraM(this->blocks[obecny].back->size.x/2.0f - this->blocks[obecny].del->size.x/2.0f,positionY,0.8f);
        this->buttonCount ++;
        this->listaButtonow.push_back(this->blocks[obecny].minus);
        this->buttonCount ++;
        this->listaButtonow.push_back(this->blocks[obecny].plus);
        this->listaSpritowBG.push_back(this->blocks[obecny].back);
        this->buttonCount ++;
        this->listaButtonow.push_back(this->blocks[obecny].del);
//            std::cout << "buttons size: " << this->listaButtonow.size() << std::endl;
//        }
    }
    if(k!=this->blocks.size()){
        this->buttonAdd->setTraM(0.0f,this->moveY - k*this->blockHeight,0.8f);
        this->buttonCount++;
        this->listaButtonow.push_back(this->buttonAdd);
    }
    Menu::run();
    for (unsigned int i = 0; i < this->blocks.size(); i++) {
//        int obecny = this->kolejnosc[i];
//        if(this->blocks[i].czyRysowac){
//            std::cout << "Wymazuje" << std::endl;
//            this->buttonCount -= 2;
//            Button *temp = this->blocks[i].plus;
//            auto itP = std::find(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].plus);

//        if(this->blocks[i].plus !=NULL){
//            this->listaButtonow.erase(std::remove(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].plus),this->listaButtonow.end());
//            this->buttonCount--;
//        }
//        if(this->blocks[i].minus!=NULL){
//            this->listaButtonow.erase(std::remove(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].minus),this->listaButtonow.end());
//            this->buttonCount--;
//
//        }
//        if(this->blocks[i].back!=NULL){
//            this->listaSpritowBG.erase(std::remove(this->listaSpritowBG.begin(),this->listaSpritowBG.end(),this->blocks[i].back)),this->listaSpritowBG.end();
//        }
//
        std::vector<Button*>::iterator itP = std::find(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].plus);
        if(itP!=this->listaButtonow.end()){
            this->listaButtonow.erase(itP);
            this->buttonCount--;
        }
        std::vector<Button*>::iterator itM = std::find(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].minus);
        if(itM!=this->listaButtonow.end()){
            this->listaButtonow.erase(itM);
            this->buttonCount--;
        }

        std::vector<Sprite*>::iterator itB = std::find(this->listaSpritowBG.begin(),this->listaSpritowBG.end(),this->blocks[i].back);
        if(itB!=this->listaSpritowBG.end()){
            this->listaSpritowBG.erase(itB);
        }
        std::vector<Button*>::iterator itD = std::find(this->listaButtonow.begin(),this->listaButtonow.end(),this->blocks[i].del);
        if(itD!=this->listaButtonow.end()){
            this->listaButtonow.erase(itD);
            this->buttonCount--;
        }

//            std::cout << "buttons size: " << this->listaButtonow.size() << std::endl;
//            for (unsigned int j = 0; j < this->listaButtonow.size(); j++) {
//                if(this->listaButtonow[j]==this->blocks[i].plus){
//                    this->listaButtonow.erase(this->blocks[i].plus);
//                    j--;
//                }
//            }
//            this->listaButtonow.push_back(this->blocks[i].plus);
//            this->listaButtonow.push_back(this->blocks[i].minus);
//            this->listaSpritowBG.push_back(this->blocks[i].back);
//        }
    }
    std::vector<Button*>::iterator it = std::find(this->listaButtonow.begin(),this->listaButtonow.end(),this->buttonAdd);
    if(it !=this->listaButtonow.end()){
        this->listaButtonow.erase(it);
        this->buttonCount--;
    }
}


void GameMenu::loadTextureFiles() {
    this->listaTekstur.push_back("../src/img/back.png");
    this->listaTekstur.push_back("../src/img/start.png");
//    this->listaTekstur.push_back("../src/img/plus.png");
//    Menu::loadTextureFiles();
}


void GameMenu::loadCoordinates() {
    this->listaWspolrzednych.push_back(glm::vec4(0,0,189.8686311322,59.078289839));
//    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
    this->listaWspolrzednych.push_back(glm::vec4(0,0,216.739619364,59.078289839));
//    this->listaWspolrzednych.push_back(glm::vec4(0,0,151.7767906718,59.078289839));
//    this->listaWspolrzednych.push_back(glm::vec4());
//    Menu::loadCoordinates();
}

void GameMenu::loadTranslates() {
    float poziomyMargines, pionowyMargines;
    poziomyMargines = -20;
    pionowyMargines = -35;
    //TODO: Sprawdzic czy dziala na wszystkich rozdzielczosciach
    this->listaPrzesuniec.push_back(glm::vec3(-1366.0f/4+pionowyMargines,-768.0f/4+poziomyMargines,0.8f));
    this->listaPrzesuniec.push_back(glm::vec3(1366.0f/4-pionowyMargines-this->listaWspolrzednych[1].z,-768.0f/4+poziomyMargines,0.8f));
//    this->listaPrzesuniec.push_back(glm::vec3(-1366.0f/4+pionowyMargines,-768.0f/4+poziomyMargines,0.8f));
//    this->listaPrzesuniec.push_back(glm::vec3(1366.0f/4-pionowyMargines-this->listaWspolrzednych[1].z,-768.0f/4+poziomyMargines,0.8f));

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
    Sprite *ramka = new Sprite(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,1366.0f/2+2*pionowyMargines,768.0f/2+2*poziomyMargines,"../src/img/ramka.png");
//    Sprite *ramka = new Sprite(0,0,1366.0f/2+2*pionowyMargines,768.0f/2+2*poziomyMargines,"../src/img/ramka.png");
    float x,y,z;
//    x= -1366.0f/4-pionowyMargines;
//    y =-768.0f/4-poziomyMargines;
//    z = 1.0f;
    x = y = 0.0f;
    ramka->setTraM(x,y,1.0f);
//    Sprite *tlo = new Sprite(-1366.0f/4-pionowyMargines,-768.0f/4-poziomyMargines,1366.0f/2+2*pionowyMargines,768.0f/2+2*poziomyMargines,"../src/img/tlo.png");
    Sprite *tlo = new Sprite(ramka->pos.x,ramka->pos.y,ramka->size.x,ramka->size.y,"../src/img/tlo.png");
    tlo->setTraM(x,y,0.2f);
    this->listaSpritowBG.push_back(tlo);
    this->listaSpritowFG.push_back(ramka);
//    Menu::loadSprites();


}


void goStart(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    inputActions::getInstance().changeState('l',window,cursor);
}

 ;
void increase(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    if(    Setting::getInstance().players[clickedButton->binds].caterpillarsCount < 10){
        Setting::getInstance().players[clickedButton->binds].caterpillarsCount++;
    }
//    std::cout << "plus" << std::endl;

}

void decrease(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    if(    Setting::getInstance().players[clickedButton->binds].caterpillarsCount > 1){
        Setting::getInstance().players[clickedButton->binds].caterpillarsCount--;
    }
//    std::cout << "minus" << std::endl;
}

void addPlayer(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    for (int i = 0; i < Setting::getInstance().players.size(); ++i) {
        if(!Setting::getInstance().players[i].czyGra){
            Setting::getInstance().players[i].czyGra = true;
            break;
        }
    }
}


void deletePlayer(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor) {
    int playerCount = 0;
    for (int i = 0; i < Setting::getInstance().players.size(); ++i) {
        if(Setting::getInstance().players[i].czyGra){
            playerCount++;
        }
    }
    if(playerCount > 2){
        Setting::getInstance().players[clickedButton->binds].czyGra = false;
    }
}





