#include "game.hpp"

Game::Game(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
   glfwSetCursor(window, NULL);  //DLACZEGO TO NIE DZIAŁĄ :(((((

   this->map= & Map::getInstance();
   this->wall = new Wall(0,vertX,0,vertY,0,maxMapHeight);
   this->lookFrom=glm::vec3(0, 400, 0);
   this->lookAt=glm::vec3(150,0,150);
   this->projection = glm::perspective(800.0f, (float)this->windowXsize/this->windowYsize , 0.001f, 20000.0f);
   glfwSetCursorPos(window,this->windowXsize/2,this->windowYsize/2);
   inputActions::getInstance().cursorFixedCenterPos=true;
}

void Game::draw(){
   this->modelView = glm::lookAt(this->lookFrom, this->lookAt, glm::vec3(0.0f, 1.0f, 0.0f));

   this->map->draw(this->projection,this->modelView);
   this->wall->draw(this->projection,this->modelView);
}

void Game::run(){
   this->testViewMov();
   this->draw();
}

void Game::testViewMov(){
   glm::vec3 viewVec=this->lookFrom-this->lookAt;
   glm::vec3 prosVec=viewVec;
   prosVec[1]=0;
   float tmp=prosVec[0];
   prosVec[0]=prosVec[2];
   prosVec[2]=tmp;
   prosVec[2]!=0? prosVec[2]=-prosVec[2] : prosVec[0]=-prosVec[0];
   //printf("%f / %f\n",prosVec[0],prosVec[2] );

   if(inputActions::getInstance().w_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom-=add*2.0f;
      this->lookAt-=add*2.0f;
   }
   if(inputActions::getInstance().s_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom+=add*2.0f;
      this->lookAt-=add;
   }
   if(inputActions::getInstance().a_pressed){
      glm::vec3 add = glm::normalize(prosVec)*2.0f;
      this->lookFrom-=add;
      this->lookAt-=add;
   }
   if(inputActions::getInstance().d_pressed){
      glm::vec3 add = glm::normalize(prosVec)*2.0f;
      this->lookFrom+=add;
      this->lookAt+=add;
   }
   if(inputActions::getInstance().movedX!=0){
      glm::mat3 rotM = glm::mat3(
         glm::vec3(cos(inputActions::getInstance().movedX/500),0.0f,sin(inputActions::getInstance().movedX/500)),
         glm::vec3(0.0f,1.0f,0.0f),
         glm::vec3(-sin(inputActions::getInstance().movedX/500),0.0f,cos(inputActions::getInstance().movedX/500))
      );
      viewVec=rotM*viewVec;
      this->lookAt=-viewVec+this->lookFrom;
   }
   if(inputActions::getInstance().movedY!=0){
      //Wg moich obliczeń na kartce to powinno działać, ale działa tak se :/
      //Pomysł był taki: obrócić wektor tak, żeby był prostopadły do osi X (vec.x =0), zapamiętać kąt
      //Standardowo obrócić go wokół OX
      //Obrócić o kąt wyliczony wczesniej

      // viewVec=this->lookFrom-this->lookAt;
      //
      // glm::vec3 vecX = viewVec;
      // vecX.x=0;
      //
      // float kat=atan(viewVec[0]/viewVec[2]);
      // vecX[2]=viewVec[2]/cos(kat);
      //  viewVec=vecX;
      // printf("%f\n",kat );
      //
      // viewVec = glm::mat3(
      //    glm::vec3(1.0f,0.0f,0.0f),
      //    glm::vec3(0.0f,cos(-inputActions::getInstance().movedY/500),-sin(-inputActions::getInstance().movedY/500)),
      //    glm::vec3(0.0f,sin(-inputActions::getInstance().movedY/500), cos(-inputActions::getInstance().movedY/500))
      // )*viewVec;
      // viewVec=glm::mat3(
      //    glm::vec3(cos(-kat),0.0f,sin(-kat)),
      //    glm::vec3(0.0f,1.0f,0.0f),
      //    glm::vec3(-sin(-kat),0.0f,cos(-kat))
      // )*viewVec;
      //
      // this->lookAt=-viewVec+this->lookFrom;

      //Tak być nie powinno! (ale jakoś działa :( )
      this->lookAt[1]-=inputActions::getInstance().movedY;
   }
}

bool Game::checkMapCollisionX(Object o){
   return this->checkMapCollisionX((float)o.getPosX());
}
bool Game::checkMapCollisionY(Object o){
   return this->checkMapCollisionY((float)o.getPosY());
}
bool Game::checkMapCollisionZ(Object o){
   return this->checkMapCollisionZ((float)o.getPosZ());
}
bool Game::checkMapCollisionX(float k){
   if(k<=0 || k>vertX) return true;
   //Kolizja z mapą X
   //.............................
   return false;
}
bool Game::checkMapCollisionY(float k){
   if( k <= 0 ) return true;
   //Kolizja z mapą Y
   //.............................
   return false;
}
bool Game::checkMapCollisionZ(float k){
   if(k<0 || k> vertY) return true;
   //kolizja z mapą Z
   //.............................
   return false;
}
