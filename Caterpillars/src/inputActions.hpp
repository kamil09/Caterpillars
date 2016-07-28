#ifndef inputCl
#define inputCl

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "state/state.hpp"
#include "state/game/game.hpp"
#include "state/menu/mainMenu/mainMenu.hpp"
#include "state/menu/mainMenu/optionMenu.hpp"
#include "state/menu/mainMenu/gameMenu.hpp"
#include "state/menu/mainMenu/loadingScreen.hpp"
#include "state/game/pauseMenu.hpp"
#include "state/game/endMenu.hpp"
#include "./state/game/player.hpp"
#include "object.hpp"
#include <thread>
#include <mutex>
#include <functional>
#include "./irrKlang/include/irrKlang.h"

#define M_PI 3.14159265358979323846

using namespace irrklang;

class State;
class inputActions{
private:

    inputActions();
    inputActions(const inputActions &);
    ~inputActions();
public:
      static inputActions& getInstance();
      void getMouseCurrentPosition(GLFWwindow *window);
      State *currentState;
      std::map<char,State*> mapStates;
      std::vector<Object*> objectPointers;
      //Będziemy zapamiętywać wciśnięcie przycisku i sprawdzać przy każdym przeliczaniu fizyki (co klatkę)
      bool keys[1024];
      bool w_pressed;
      bool a_pressed;
      bool s_pressed;
      bool d_pressed;
      bool space_pressed;
      bool i_pressed;
      bool escape_pressed;
      bool SHIFT_pressed;
      //Zerowane przy każdym przeliczniu fizyki
      int scroll;
      //Gdy wciśnięty przycisk true (ładujemy wtedy broń np, celujemy itp);
      bool leftClick;
      bool rightClick;
      //Gdy true oznacza to, że przed chwilą zwolniono przycik myszy, należy wyzerować i zrobić jakąś akcję na podstawie cursorLastX, cursorLastY
      bool lastLeftClick;
      double cursorLastX;
      double cursorLastY;
      //Wskazuje o ile przesnięto myszę od ostatniej klatki (używane do sterowania kamerą)
      double movedX;
      double movedY;
      //Tych 2 zmiennych poniżej nie używać! potrzebne do wyliczanie tych 2 zmiennych wyżej ;)
      double lastX;
      double lastY;
      bool cursorFixedCenterPos;
      bool cursorDisabled;
      void clear();
      double getCursorLastX();
      double getCursorLastY();

      GLfloat deltaTime = 0.0f;//Czas pomiedzy klatkami

      Player *winner;

      ISoundEngine *SoundEngine;//dzwiek

      GLFWcursor * setCallbacks(GLFWwindow *window, GLFWcursor *cursor);
      static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods );
      static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
      static void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);
      static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

      void changeCursor(int shape);
      float *pixelData;
      int cursorShape;
      State *findState(char key, GLFWwindow *window, GLFWcursor *cursor);
      State *createState(char key, GLFWwindow *window, GLFWcursor *cursor);
      void changeState(char key, GLFWwindow *window, GLFWcursor *cursor);
        void createSoundEngine();
      //irrklang::ISoundEngine *soundEngine;
};


#endif
