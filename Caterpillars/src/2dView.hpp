#ifndef menu
#define menu
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "settings.hpp"
#include "button.hpp"

using namespace std;

enum gameCaseType {START,OPTIONS,INFO,GAME,PAUSE,GAME_END,EXIT};
extern gameCaseType gameCase;

void init2d();
void del2d();

void mainMenuView();
void optionsView();
void infoView();
void gameEndView();
void exitView();

#endif
