//
// Created by lewin on 10.07.16.
//

#ifndef PAUSEMENU
#define PAUSEMENU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../menu/button.hpp"
#include "../menu/mainMenu/subMenu.hpp"

class PauseMenu : public SubMenu{
public:
    virtual void pressESC() override;

    virtual void loadCallBacks() override;

    virtual void loadTextureFiles() override;

    virtual void loadCoordinates() override;

    virtual void loadTranslates() override;

    virtual void loadSprites() override;
    Font *font;
    PauseMenu(State *state, GLFWwindow *window, GLFWcursor *cur);
};



void goExit(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor);
void goBack2(Button *clickedButton, GLFWwindow *window, GLFWcursor *cursor);

#endif //CATERPILLARS_PAUSEMENU_HPP
