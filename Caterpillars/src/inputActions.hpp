#ifndef inputCl
#define inputCl

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "state/state.hpp"
#include "state/game/game.hpp"
// #include "state/menu/menu.hpp"

// class Game;
class State;
// enum class gameCaseType {MAIN=0,START=1,START_WIELU=2,OPTIONS=3,EXIT=4,INFO=5,GAME_ST=6,PAUSE=7,GAME_END=8};
class inputActions{
   public:
      inputActions();
      inputActions(const inputActions &);
      ~inputActions();
      static inputActions& getInstance();
      void getMouseCurrentPosition(GLFWwindow *window);
      State *currentState;
    //   gameCaseType nextState;
    //   bool changeState;
      //Będziemy zapamiętywać wciśnięcie przycisku i sprawdzać przy każdym przeliczaniu fizyki (co klatkę)
      bool w_pressed;
      bool a_pressed;
      bool s_pressed;
      bool d_pressed;
      bool space_pressed;
      bool i_pressed;
      bool escape_pressed;
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

      void clear();
      double getCursorLastX();
      double getCursorLastY();

      void setCallbacks(GLFWwindow* window,GLFWcursor* cursor);
      static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods );
      static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
      static void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);
      static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

      void changeCursor(int shape);
      float *pixelData;
      int cursorShape;
      void changeMenu(GLFWwindow* window,GLFWcursor* cursor);
      void changeGame(GLFWwindow* window,GLFWcursor* cursor);
};


#endif
