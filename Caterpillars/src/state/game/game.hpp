#ifndef GAME
#define GAME

#include "../state.hpp"
#include "map/map.hpp"

class Game : public State{
public:
    Game(GLFWwindow *window,GLFWcursor *cur);
    void run() override;
    void draw() override;
    Map *map;

};

#endif
