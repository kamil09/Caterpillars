//
// Created by lewin on 06.07.16.
//

#ifndef SUBMENU
#define SUBMENU

#include "../menu.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../../state.hpp"

class SubMenu : public Menu{
public:
    virtual void pressESC() override;

    SubMenu(State *state, GLFWwindow *window, GLFWcursor *cur);
    State *primaryState;

    virtual void draw() override;

};
void goBack(Button *state, GLFWwindow *window, GLFWcursor *cursor);

#endif //CATERPILLARS_SUBMENU_HPP
