//
// Created by lewin on 07.07.16.
//

#ifndef GAMEMENU
#define GAMEMENU

#include "../../state.hpp"
#include "../menu.hpp"
#include "subMenu.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../../../settings.hpp"
#include <algorithm>
#include <thread>
#include <functional>
#include "../../game/map/map.hpp"

struct block{
    Sprite *back;
    int playerNumber;
    Button *plus;
    Button *minus;
    Button *del;
//    bool czyRysowac;
};

class GameMenu : public SubMenu{
public:
    std::vector<block> blocks;
    std::vector<int> kolejnosc;

    virtual void run() override;

    Button *buttonAdd;
    float blockHeight;
    float moveY;
    virtual void loadSprites() override;
    Font *font;
    GameMenu(State *state, GLFWwindow *window, GLFWcursor *cur);
    void loadTextureFiles() override;
    void loadCoordinates() override;
    void loadTranslates() override;
    virtual void loadCallBacks() override;
    void createBlocks();
};
void goStart(Button *state, GLFWwindow *window, GLFWcursor *cursor);
void increase(Button *state, GLFWwindow *window, GLFWcursor *cursor);
void decrease(Button *state, GLFWwindow *window, GLFWcursor *cursor);
void addPlayer(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor);
void deletePlayer(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor);

#endif //CATERPILLARS_GAMEMENU_HPP
