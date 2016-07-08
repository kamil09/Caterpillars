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



class GameMenu : public SubMenu{
public:
    virtual void loadSprites() override;
    Font *font;
    GameMenu(State *state, GLFWwindow *window, GLFWcursor *cur);
    void loadTextureFiles() override;
    void loadCoordinates() override;
    void loadTranslates() override;
    virtual void loadCallBacks() override;

};
void goStart(State *state, GLFWwindow *window, GLFWcursor *cursor);

#endif //CATERPILLARS_GAMEMENU_HPP
