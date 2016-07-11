//
// Created by lewin on 09.07.16.
//

#ifndef LOADINGSCREEN
#define LOADINGSCREEN


#include "subMenu.hpp"

class LoadingScreen : public SubMenu{
public:
    virtual void run() override;

    LoadingScreen(State *state, GLFWwindow *window, GLFWcursor *cur);
    bool czyTworzyc;
};

#endif //CATERPILLARS_LOADINGSCREEN_HPP
