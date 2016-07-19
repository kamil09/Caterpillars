//
// Created by lewin on 16.07.16.
//

#include "player.hpp"
#include "../../models/caterpillar.hpp"

Player::Player(int id) {
    this->id = id;
    this->nazwa = Setting::getInstance().players[this->id].nazwa;
    this->kolor = Setting::getInstance().players[this->id].kolor;
    int caterpillarCount = Setting::getInstance().players[this->id].caterpillarsCount;
    for (int i = 0; i < caterpillarCount; ++i) {
        Caterpillar *cat = new Caterpillar(this,(char*)"../src/obj/caterpillar.obj");
        this->caterpillars.push_back(cat);
        this->aliveCaterpillars.push_back(cat);
    }
}


Caterpillar * Player::changeCaterpillar() {
    if(this->aliveCaterpillars.empty()){
        return nullptr;
    }
    this->activeCaterpillar++;
    this->activeCaterpillar = this->activeCaterpillar % this->aliveCaterpillars.size();
    return this->aliveCaterpillars[this->activeCaterpillar];
}

