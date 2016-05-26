#include "game.hpp"
#include "../../inputActions.hpp"


Game::Game(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){

   this->map= & Map::getInstance();
   this->wall = new Wall(0,vertX,0,vertY,0,maxMapHeight*1.3);
   this->targetView = new object2D(-60,-60,120,120,(char*)"../src/img/target-viewfinder.png");
   this->rose = new object2D(-200,-200,400, 400,(char*)"../src/img/rose.png");
   this->rose->setTraM(0.8,-0.8,0.0f);

   this->caterrVec.push_back( new Caterpillar((char*)"../src/obj/caterpillar.obj") );
   //this->caterrVec[0]->setPos(rand()%vertX,maxMapHeight + 300,rand()%vertY); // Tutaj usunac 200 Pawelek
   this->caterrVec[0]->setPos(0,0,0);

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

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   for(int i=0;i < (int)this->caterrVec.size(); i++)
      this->caterrVec[i]->draw(this->projection,this->modelView);
   this->targetView->draw();

   this->drawRose();
   glDisable(GL_BLEND);
}
/*
 * DO POPRAWY !!!
*/
void Game::drawRose(){
   glm::vec2 look,wind;
   look.x=this->lookAt.x-this->lookFrom.x;
   look.y=this->lookAt.z-this->lookFrom.z;
   wind.x=this->map->windForce.x;
   wind.y=this->map->windForce.z;
   look=glm::normalize(look);
   wind=glm::normalize(wind);
   double lookD = sqrt( (look.x*look.x)+(look.y*look.y) );
   double windD = sqrt( (wind.x*wind.x)+(wind.y*wind.y) );
   double cosK;

   cosK= ((look.x*wind.x) + (look.y*wind.y)) / (lookD*windD);


   double kat = -acos(cosK);
   float p = look.x*wind.y-look.y*wind.x;
   if(p>0) kat*=-1;

   //kat=1;
   //std::cout << cosK <<"   -- " <<kat << " " << lookD << " " << windD << std::endl;
   if(kat!=kat) kat=0;
   glm::mat4 rotM = glm::mat4(
      glm::vec4(cos(kat),-sin(kat),0.0f,0.0f),
      glm::vec4(sin(kat),cos(kat),0.0f,0.0f),
      glm::vec4(0.0f,0.0f,1.0f,0.0f),
      glm::vec4(0.0f,0.0f,0.0f,1.0f)
   );
   this->rose->rotM=rotM;
   this->rose->draw();
}
void Game::run(){
   //this->map->kaboom(rand()%1000,rand()%1000,rand()%500,rand()%20+30 );
   this->testViewMov();
   this->draw();

   for(int i=0;i < (int)this->caterrVec.size(); i++)
      this->caterrVec[i]->recalculateGravity();
}

void Game::testViewMov(){
   glm::vec3 viewVec=this->lookAt-this->lookFrom;
   glm::vec3 prosVec=viewVec;
   prosVec[1]=0;
   float tmp=prosVec[0];
   prosVec[0]=prosVec[2];
   prosVec[2]=tmp;
   prosVec[2]!=0? prosVec[2]=-prosVec[2] : prosVec[0]=-prosVec[0];
   //printf("%f / %f\n",prosVec[0],prosVec[2] );

   if(inputActions::getInstance().w_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom+=add*2.0f;
      this->lookAt+=add*2.0f;
   }
   if(inputActions::getInstance().s_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom-=add*2.0f;
      this->lookAt-=add*2.0f;
   }
   if(inputActions::getInstance().a_pressed){
      glm::vec3 add = glm::normalize(prosVec)*2.0f;
      this->lookFrom+=add;
      this->lookAt+=add;
   }
   if(inputActions::getInstance().d_pressed){
      glm::vec3 add = glm::normalize(prosVec)*2.0f;
      this->lookFrom-=add;
      this->lookAt-=add;
   }
   if(inputActions::getInstance().movedX!=0){
      glm::mat3 rotM = glm::mat3(
         glm::vec3(cos(inputActions::getInstance().movedX/500),0.0f,sin(inputActions::getInstance().movedX/500)),
         glm::vec3(0.0f,1.0f,0.0f),
         glm::vec3(-sin(inputActions::getInstance().movedX/500),0.0f,cos(inputActions::getInstance().movedX/500))
      );
      viewVec=rotM*viewVec;

      this->lookAt=viewVec+this->lookFrom;
   }
   if(inputActions::getInstance().movedY!=0){
      //Wg moich obliczeń na kartce to powinno działać, ale działa tak se :/

      // float kat = inputActions::getInstance().movedY/500;
      // viewVec=this->lookFrom-this->lookAt;
      //
      // glm::vec3 vecX = glm::vec3(0.0f,viewVec[1]/2,viewVec[2]);
      // glm::vec3 vecZ = glm::vec3(viewVec[0],viewVec[1]/2,0.0f);
      // float sum = fabs(viewVec.x)+fabs(viewVec.z);
      // float katX = -kat*viewVec.x/sum;
      // float katZ =  -kat*viewVec.z/sum;
      //
      // glm::mat3 rotXM = glm::mat3(
      //    glm::vec3(1.0f,0.0f,0.0f),
      //    glm::vec3(0.0f,cos(katX),-sin(katX)),
      //    glm::vec3(0.0f,sin(katX), cos(katX))
      // );
      // glm::mat3 rotZM = glm::mat3(
      //    glm::vec3(cos(katZ),-sin(katZ),0.0f),
      //    glm::vec3(sin(katZ),cos(katZ),0.0f),
      //    glm::vec3(0.0f,0.0f, 1.0f)
      // );
      //
      // vecX = rotXM*vecX;
      // vecZ = rotZM*vecZ;
      //
      // viewVec = vecX+vecZ;
      //
      // this->lookAt=-viewVec+this->lookFrom;

      //Tak być nie powinno! (ale jakoś działa :( )
      this->lookAt[1]-=inputActions::getInstance().movedY;
   }
}

 bool Game::checkMapCollisionX(Object o){
   return checkMapCollisionX((float)o.posX);
}
 bool Game::checkMapCollisionY(Object o){

    //Pawelek
    if((float)o.posY - 25 <= Map::getInstance().mapVert[(int)o.posX][(int)o.posZ]) // Tu ta 30 jest troche slaba
    {
      cout << "Mniejsze niz mapa!" << endl;
      return true;
    }

   return checkMapCollisionY((float)o.posY);
}
 bool Game::checkMapCollisionZ(Object o){
   return checkMapCollisionZ((float)o.posZ);
}
 bool Game::checkMapCollisionX(float k){
   if(k<=3 || k>vertX-3) return true;
   //Kolizja z mapą X
   //.............................
   return false;
}
 bool Game::checkMapCollisionY(float k){
   if( k <= 0 )
    return true;
   //Kolizja z mapą Y
   //.............................
   return false;
}
 bool Game::checkMapCollisionZ(float k){
   if(k<=3 || k>vertY-3) return true;
   //kolizja z mapą Z
   //.............................
   return false;
}
