#include "2dView.hpp"

gameCaseType gameCase;

//Przełączamy się na rysowanie w 2d
//TO działa dla openGL 2.0 nie wiem jak z 3.3
void init2d(){
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0.0, Setting::getInstance().getWidth(), Setting::getInstance().getHeight(), 0.0, -1.0, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_CULL_FACE);
   glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
   glDisable(GL_DEPTH_TEST);  // disable depth-testing
   glClear(GL_DEPTH_BUFFER_BIT);

}
void del2d(){
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void mainMenuView(){
   init2d();
   //DRAW MENU
   del2d();
};
void optionsView(){
   init2d();

   del2d();
};
void infoView(){
   init2d();

   del2d();
};
void gameEndView(){
   init2d();

   del2d();
};
void exitView(){
   init2d();

   del2d();
};

void gameView(){
   init2d();

   del2d();
};
void pauseView(){
   init2d();

   del2d();
};
