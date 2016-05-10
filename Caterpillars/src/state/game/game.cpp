#include "game.hpp"

Game::Game(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
   this->map= & Map::getInstance();
}

void Game::draw(){
   this->map->draw();
}

void Game::run(){
   Map::getInstance().testViewMov();
   this->draw();
}
