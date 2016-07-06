//
// Created by lewin on 06.07.16.
//

#ifndef OPTIONMENU
#define OPTIONMENU

#include "../../state.hpp"
#include "../menu.hpp"
#include "subMenu.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../../../settings.hpp"



class OptionMenu : public SubMenu{
public:
    virtual void loadSprites() override;

    OptionMenu(Menu *menu,GLFWwindow *window,GLFWcursor *cur);
    void loadTextureFiles() override;
    void loadCoordinates() override;
    void loadTranslates() override;
    virtual void loadCallBacks() override;
    void settingsPrint(Sprite *sprite);
    std::vector<std::string> ustawieniaTeksty;
    void readSettings();
    std::string checkBool(bool doTestu);
};

#endif //CATERPILLARS_OPTIONMENU_HPP
