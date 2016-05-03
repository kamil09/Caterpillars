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

      bool leftClick;
      bool rightClick;

};


#endif
