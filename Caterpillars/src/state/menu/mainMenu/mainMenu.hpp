#ifndef MAIN_MENU
#define MAIN_MENU

#include "../menu.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../../state.hpp"
#include "optionMenu.hpp"
// #include "../../../font.hpp"

class MainMenu : public Menu{
public:
    virtual void loadSprites() override;

    MainMenu(GLFWwindow *window,GLFWcursor *cur);
    void loadTextureFiles() override;
    void loadCoordinates() override;
    void loadTranslates() override;

    virtual void loadCallBacks() override;

    // ~MainMenu();
    // Font *font;
};
void singlePlayer(State *state, GLFWwindow *window, GLFWcursor *cursor);
void multiPlayer(State *state, GLFWwindow *window, GLFWcursor *cursor);
void options(State *state, GLFWwindow *window, GLFWcursor *cursor);
void exitWindow(State *state, GLFWwindow *window, GLFWcursor *cursor);

#endif
