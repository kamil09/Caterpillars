#ifndef settings
#define settings

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

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
      char* rankFileName;
      void loadFromFile(FILE *in);
   public:
      Setting();
      Setting(const Setting &);
      ~Setting();
      void load();
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
      char *getRankFileName();
};


#endif
