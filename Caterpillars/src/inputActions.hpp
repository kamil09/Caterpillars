#ifndef inputCl
#define inputCl

#include <iostream>

class inputActions{
   public:
      inputActions();
      inputActions(const inputActions &);
      ~inputActions();
      static inputActions& getInstance();

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
};


#endif
