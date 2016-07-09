#ifndef settings
#define settings

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct player{
    glm::vec4 kolor;
    std::string nazwa;
    int caterpillarsCount;
    bool czyGra;
};

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
    std::vector<player> players;
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
