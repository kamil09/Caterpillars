#include "game.hpp"

Game::Game(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
   glfwSetCursor(window, NULL);  //DLACZEGO TO NIE DZIAŁĄ :(((((

   this->map= & Map::getInstance();
   this->lookFrom=glm::vec3(0, 400, 0);
   this->lookAt=glm::vec3(150,0,150);
   this->projection = glm::perspective(2000.0f, (float)this->windowXsize/this->windowYsize , 0.001f, 20000.0f);
   glfwSetCursorPos(window,this->windowXsize/2,this->windowYsize/2);
   inputActions::getInstance().cursorFixedCenterPos=true;
}

void Game::draw(){
   this->modelView = glm::lookAt(this->lookFrom, this->lookAt, glm::vec3(0.0f, 1.0f, 0.0f));

   this->map->shader->useShaderProgram(0);
   GLint iProjectionLoc = glGetUniformLocation(this->map->shader->shaderProgram[0], "projectionMatrix");
   GLint iModelViewLoc = glGetUniformLocation(this->map->shader->shaderProgram[0], "modelViewMatrix");

   glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection));
   glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(this->modelView));

   this->map->draw();
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

   if(inputActions::getInstance().w_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom-=add*2.0f;
      this->lookAt-=add*2.0f;
   }
   if(inputActions::getInstance().s_pressed){
      glm::vec3 add = glm::normalize(viewVec);
      this->lookFrom+=add*2.0f;
      this->lookAt-=add*2.0f;
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
         glm::vec3(cos(inputActions::getInstance().movedX/300),0.0f,sin(inputActions::getInstance().movedX/300)),
         glm::vec3(0.0f,1.0f,0.0f),
         glm::vec3(-sin(inputActions::getInstance().movedX/300),0.0f,cos(inputActions::getInstance().movedX/300))
      );
      viewVec=rotM*viewVec;
      this->lookAt=-viewVec+this->lookFrom;
   }
   if(inputActions::getInstance().movedY!=0){
      viewVec=this->lookFrom-this->lookAt;
      float vecLen = sqrt(pow(viewVec[0],2)+pow(viewVec[1],2)+pow(viewVec[2],2));
      this->lookAt[1]-=inputActions::getInstance().movedY/2;
      viewVec=this->lookFrom-this->lookAt;
      //Przekształcenia wzorów na długość wektora aby uzyskać nowe współrzędne (inna współrzędna Y, ale ta sama długość)
      float rightVal = -(pow(vecLen,2)-pow((this->lookFrom[1]-this->lookAt[1]),2)-pow(this->lookFrom[0],2)-pow(this->lookFrom[2],2));
      //No nie no... delta :)
      float wspA = pow(this->lookAt[0],2)+pow(this->lookAt[2],2);
      float wspB = -2*(this->lookFrom[0]*this->lookAt[0] + this->lookFrom[2]*this->lookAt[2]);
      float coef = (-wspB- sqrt(pow(wspB,2)-(4*rightVal*wspA) ) )/(2*wspA);
      if(coef < 0)
         coef = (-wspB+ sqrt(pow(wspB,2)-(4*rightVal*wspA) ) )/(2*wspA);
   }
}
