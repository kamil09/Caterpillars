#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"

class Game : public State{
    Game();
    void run() override;
    void draw() override;
    Map *map;

};

#endif
