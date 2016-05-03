#ifndef settings
#define settings

#include <iostream>
#include "string.h"

class Setting {
   private:
      int width;
      int height;
      bool fullWindow;
      bool fullResolution;
      bool music;
      bool sounds;
      int difficulty;
      int frames;
      std::string rankFileName;
   public:
      Setting();
      Setting(const Setting &);
      ~Setting();
      static Setting& getInstance();
      //NIE ROBIMY SETTERÓW, nie pozwalamy na zmiany ustawień
      int getWidth();
      int getHeight();
      bool getFullWindow();
      bool getFullResolution();
      bool getMusic();
      bool getSounds();
      int getDifficulty();
      int getFrames();
      std::string getRankFileName();
};


#endif
