//
// Created by lewin on 23.07.16.
//

#ifndef ENDMENU_HPP
#define ENDMENU_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../menu/button.hpp"
#include "../menu/mainMenu/subMenu.hpp"

class EndMenu : public SubMenu {
public:
    EndMenu(State *state, GLFWwindow *window, GLFWcursor *cur);
    virtual void loadCallBacks() override;
    virtual void loadTextureFiles() override;
    virtual void loadCoordinates() override;
    virtual void loadTranslates() override;
    virtual void loadSprites() override;

    virtual void pressESC() override;

    Font *font;
};


#endif //CATERPILLARS_ENDMENU_HPP
