#include "game.hpp"
#include <typeinfo>
#include "../../inputActions.hpp"


Game::Game(GLFWwindow *window,GLFWcursor *cur) : State(window,cur){
   this->sunPosition=glm::vec3(100,1000,100);

   this->map= & Map::getInstance();
   //this->wall = new Wall(0,vertX,0,vertY,0,maxMapHeight*1.3);
   this->wall = new Wall((char*)"../src/obj/wall.obj",0,vertX,0,vertY,0,maxMapHeight*1.3);
//   this->targetView = new object2D(-60,-60,120,120,(char*)"../src/img/target-viewfinder.png");
   this->targetView = new Sprite(-30, -30, 60, 60, (char *) "../src/img/target-viewfinder.png");
//   this->rose = new object2D(-200,-200,400, 400,(char*)"../src/img/rose.png");
   float roseWidth, roseHeight;
   roseWidth = roseHeight = 200;
   this->rose = new Sprite(-roseWidth / 2, -roseHeight / 2, roseWidth, roseHeight, (char *) "../src/img/rose.png");
//   this->rose->setTraM(0.8,-0.8,0.0f);
//   this->rose->initFont("../src/fonts/Arial.ttf", 32);
//   this->targetView->initFont("../src/fonts/Arial.ttf", 32);
//   this->targetView->addTextL("Wind Rose", 0,0, 1, (glm::vec3(0.0f,0.0f,0.0f)));
//    this->rose->addTextM("Wind Rose", 0,0, 1, (glm::vec3(0.0f,0.0f,0.0f)));
//   int width,height;
//   glfwGetWindowSize(window, &width,&height);
   std::cout << "Width: " << this->windowXsize <<  " rW: " << (this->windowXsize-roseWidth)/2 << " height: " << this->windowYsize << " rH " << -(this->windowYsize-roseHeight)/2;

    //TODO: sprawdzic czy dziala dla wszystkich rozdzielczosci
    this->rose->setTraM((1366.0f-roseWidth)/2,-(768.0f-roseHeight)/2,0.0f);
//   this->rose->setTraM((this->windowXsize-roseWidth)/2,-(this->windowYsize-roseHeight)/2,0.0f);
    this->projection = glm::perspective(45.0f, (float)this->windowXsize/this->windowYsize , 0.001f, 1000.0f);

    //Dodawanie Caterpillarow
    for(int i=0;i<1;i++) {
       Caterpillar *cat = new Caterpillar((char*)"../src/obj/caterpillar.obj");
       cat->font = new Font("../src/fonts/Coalition.ttf",400,this->projection);
       this->caterrVec.push_back( cat );
       inputActions::getInstance().objectPointers.push_back(cat);

       this->caterrVec[i]->setPos(rand() % vertX/2+(vertY/4),maxMapHeight + 200,rand() % vertY/2+(vertY/4)); // Tutaj usunac 200 Pawelek
       this->caterrVec[i]->teamID = (i%2)+1;
       std::cout << endl << this->caterrVec[i]->teamID;
   }
    float min1=999;
    float min2=999;
    for(int i=0;i<100; i++) for(int k=0;k<100;k++) if (this->map->mapVert[i][k]<min1) min1=this->map->mapVert[i][k];
    for(int i=vertX-100;i<vertX; i++) for(int k=vertY-100;k<vertY;k++) if (this->map->mapVert[i][k]<min2) min2=this->map->mapVert[i][k];
    this->towers.push_back(new Tower ((char*)"../src/obj/tower.obj" ,50,min1,50,80,200 ));
    this->towers.push_back(new Tower ((char*)"../src/obj/tower.obj", vertX-50,min2,vertY-50,260,380) );
    inputActions::getInstance().objectPointers.push_back(this->towers[0]);
    inputActions::getInstance().objectPointers.push_back(this->towers[1]);

    this->lightsMat = glm::mat4(0);
    if(this->towers.size() > 0 ) this->lightsMat[0] = glm::vec4(this->towers[0]->pos.x,this->towers[0]->pos.y,this->towers[0]->pos.z,0.0f);
    if(this->towers.size() > 1 ) this->lightsMat[2] = glm::vec4(this->towers[1]->pos.x,this->towers[1]->pos.y,this->towers[1]->pos.z,0.0f);


    //Ustawianie aktualnego Caterpillara - pierwszy w tablicy catterVec

    this->currentCutterpillar = this->caterrVec[0];

    //ta wartosc wskazuje nam ktory jest aktyalny
    //wykorzystywana w kolizjach
    Game::currCatIndex = 0;


    this->lookFrom=glm::vec3(0, 400, 0);
    this->lookAt=glm::vec3(150,0,150);


   glfwSetCursorPos(window,this->windowXsize/2,this->windowYsize/2);
   inputActions::getInstance().cursorFixedCenterPos=true;
}

int Game::currCatIndex;

void Game::draw(){

   if(this->towers.size() > 0 ) this->lightsMat[1] = this->towers[0]->light->lightDir;
   if(this->towers.size() > 1 ) this->lightsMat[3] = this->towers[1]->light->lightDir;
   this->modelView = glm::lookAt(this->lookFrom, this->lookAt, glm::vec3(0.0f, 1.0f, 0.0f));

   this->map->draw(this->projection,this->modelView, this->lightsMat,this->sunPosition);
   this->wall->draw(this->projection,this->modelView, this->lightsMat,this->sunPosition);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for(int i=0;i < (int)this->caterrVec.size(); i++){
        if((this->caterrVec[i] != this->currentCutterpillar) || (this->currentCutterpillar->viewBack < -20))
            //for (int j = 0; j < 10; j++) {
            //    this->caterrVec[i]->setPos(100.0f*j,0.0f,100.0f*j);
            //    this->caterrVec[i]->draw(this->projection,this->modelView);
            //}
        this->caterrVec[i]->draw(this->projection,this->modelView,this->lightsMat,this->sunPosition);

    }
    for(int i=0;i<(int)this->towers.size();i++ )
      this->towers[i]->draw(this->projection,this->modelView,this->lightsMat,this->sunPosition);

    if(!(this->currentCutterpillar->viewBack < -20))
      this->targetView->draw();

   this->drawRose();
   glDisable(GL_BLEND);
}

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
//   glm::mat4 rotM = glm::rotate(glm::mat4(1),(float)kat,glm::vec3(0.0f,0.0f,1.0f));
   this->rose->rotM=rotM;
   this->rose->draw();
}
void Game::run(){
   //this->map->kaboom(rand()%1000,rand()%1000,rand()%500,rand()%20+30 );
   if(inputActions::getInstance().SHIFT_pressed) this->testViewMov();
   else {
      this->catterMove();
      this->calcViewMatrix();
   }
   this->draw();

   for(int i=0;i < (int)this->caterrVec.size(); i++){
      this->caterrVec[i]->recalculateGravity();
      this->caterrVec[i]->recalculateMatrix();
   }
   for(int i=0; i< (int)this->towers.size() - 1;i++ )
     this->towers[i]->light->moveLight();

   //Pociski
   if((int)this->bullets.size() > 0)
   {
     for(int i=0; i < (int)this->bullets.size(); i++)
     {

       this->bullets[i]->recalculateGravity();
       this->bullets[i]->recalculateMatrix();
       cout << "Bullet : " << i << " Position: " << this->bullets[i]->pos.x << ", " <<
       this->bullets[i]->pos.y << ", " << this->bullets[i]->pos.z << endl;

      }
    }
}
void Game::calcViewMatrix(){
   this->lookAt = this->currentCutterpillar->startLook;
   this->lookAt = glm::mat3(this->currentCutterpillar->rotM) * this->lookAt;

   this->lookFrom = this->currentCutterpillar->pos;
   this->lookAt+=this->currentCutterpillar->pos;

   this->lookFrom.y+= 6*this->currentCutterpillar->size.y;
   this->lookAt.y+= 6*this->currentCutterpillar->size.y;

   glm::vec3 look = this->lookAt - this->lookFrom;
   this->lookFrom += glm::normalize(look)*this->currentCutterpillar->viewBack;

   //std::cout << this->currentCutterpillar->viewBack << std::endl;


   // this->lookFrom.x -= this->currentCutterpillar->size.x;
   // this->lookAt.x-= this->currentCutterpillar->size.x;
   //
   // this->lookFrom.z -= this->currentCutterpillar->size.z;
   // this->lookAt.z-= this->currentCutterpillar->size.z;
   //this->lookFrom.z-= this->currentCutterpillar->size.z;

}
void Game::catterMove(){
   this->end = clock();
	float diff = ((float)this->end - (float)this->start);
   diff/=CLOCKS_PER_SEC;
   //std::cout << diff << std::endl;
   glm::vec3 catViewVec = this->currentCutterpillar->startLook;
   glm::mat3 rotY = glm::mat3(
		glm::vec3(cos(this->currentCutterpillar->rot.y),0.0f, sin(this->currentCutterpillar->rot.y)),
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(-sin(this->currentCutterpillar->rot.y),0.0f,cos(this->currentCutterpillar->rot.y))
	);

   glm::vec3 shotViewVec = glm::mat3(this->currentCutterpillar->rotM) * this->currentCutterpillar->startLook;

   catViewVec = rotY * catViewVec;
   glm::vec3 prosVec=catViewVec;
   prosVec[1]=0;
   float tmp=prosVec[0];
   prosVec[0]=prosVec[2];
   prosVec[2]=tmp;
   prosVec[2]!=0? prosVec[2]=-prosVec[2] : prosVec[0]=-prosVec[0];
   // //printf("%f / %f\n",prosVec[0],prosVec[2] );

   glm::vec3 newPos = this->currentCutterpillar->pos;
   if(!inputActions::getInstance().space_pressed && this->currentCutterpillar->on_the_ground){

     if(inputActions::getInstance().w_pressed){
        glm::vec3 add = glm::normalize(catViewVec);
        newPos+=add*diff*this->currentCutterpillar->maxWalkSpeed*20.0f;
     }
     if(inputActions::getInstance().s_pressed){
        glm::vec3 add = glm::normalize(catViewVec);
        newPos-=add*diff*this->currentCutterpillar->maxWalkSpeed*20.0f;
     }
     if(inputActions::getInstance().a_pressed){
        glm::vec3 add = glm::normalize(prosVec)*2.0f;
        newPos+=add*diff*this->currentCutterpillar->maxWalkSpeed*10.0f;
     }
     if(inputActions::getInstance().d_pressed){
        glm::vec3 add = glm::normalize(prosVec)*2.0f;
        newPos-=add*diff*this->currentCutterpillar->maxWalkSpeed*10.0f;
     }
     //Warunek na strzal - widok z celowikiem i lewy przycisk
     if(inputActions::getInstance().leftClick && !(this->currentCutterpillar->viewBack < -20))
     {

       if( shotPower >= maxShotPower )
          shotPower = 0;

       //Wybieranie sily strzalu:
       shotPower = shotPower + 0.05;
       powerischoosed = true;
       calculatedDamage = 0;

       shot.x = 0;
       shot.y = 0;
       shot.z = 0;

       //Siła do strzalu
       cout <<"POWER: " << shotPower << endl;

     }
     //Po wyborze sily strzaly nastepuje strzal
     if(!inputActions::getInstance().leftClick && powerischoosed)
     {
       //Wyliczenie damage
       calculatedDamage =  (std::rand() % (int)(this->currentCutterpillar->weapon->maxDamage -
           this->currentCutterpillar->weapon->minDamage) ) +
           this->currentCutterpillar->weapon->minDamage;


       cout << "Damage: " << calculatedDamage << endl;

       //tworzenie obiektu Bullet
       Bullet *bullecik = new Bullet ((char*)"../src/obj/bullet.obj" , calculatedDamage);
       //ustawienie pozycji poczatkowej
       bullecik->setPos(this->currentCutterpillar->pos.x, this->currentCutterpillar->pos.y, this->currentCutterpillar->pos.z);
       //bullecik->setPos(200,500,200);
       //ustawienie szybkosci wystrzelonego pocisku
       shot.x = shotViewVec.x * shotPower;
       shot.y = shotViewVec.y * shotPower;
       shot.z = shotViewVec.z * shotPower;

       //dodanie wyzej stworzonego obiektu do listy pociskow
       this->bullets.push_back( bullecik );
       //dodanie do listy wszystkich obiektow
       inputActions::getInstance().objectPointers.push_back( bullecik );

       this-> bullets.back()->diagonalThrow(shot);

       powerischoosed = false;
       shotPower = 0;

       //cout << endl << shot.x << " : " << shot.y << " : " << shot.z << endl << endl;

     }
 }
   else if(inputActions::getInstance().space_pressed){
     if(this->currentCutterpillar->on_the_ground)
     {
      int jump_coefficient = 1;
      glm::vec3 shot;
      //skok w przod
      if(inputActions::getInstance().w_pressed){
         shot.x = catViewVec.x * jump_coefficient;
         shot.z = catViewVec.z * jump_coefficient;
      }
      //skok w tyl
      if(inputActions::getInstance().s_pressed){
        shot.x = catViewVec.x * -jump_coefficient;
        shot.z = catViewVec.z * -jump_coefficient;
      }
      if(inputActions::getInstance().a_pressed){
         shot.x = prosVec.x * jump_coefficient;
         shot.z = prosVec.z * jump_coefficient;
      }
      //skok w tyl
      if(inputActions::getInstance().d_pressed){
        shot.x = prosVec.x * -jump_coefficient;
        shot.z = prosVec.z * -jump_coefficient;
      }

      //shot.x = 0;
      shot.y = 3;
      //shot.z = 0;
      this->currentCutterpillar->diagonalThrow(shot);
    }
  }


   checkCollisionAndMove(this->currentCutterpillar,newPos,inputActions::getInstance().objectPointers);
   if(inputActions::getInstance().movedX!=0){
      this->currentCutterpillar->rot.y+=(float)(inputActions::getInstance().movedX)/500;
      if(this->currentCutterpillar->rot.y<-2*M_PI) this->currentCutterpillar->rot.y+=2*M_PI;
      if(this->currentCutterpillar->rot.y>2*M_PI) this->currentCutterpillar->rot.y-=2*M_PI;
   }
   if(inputActions::getInstance().movedY!=0){
      this->currentCutterpillar->rot.z+=(float)(inputActions::getInstance().movedY)/500;
      if(this->currentCutterpillar->rot.z<-M_PI/3) this->currentCutterpillar->rot.z=-M_PI/3;
      if(this->currentCutterpillar->rot.z>M_PI/3) this->currentCutterpillar->rot.z=M_PI/3;
   }
   if(inputActions::getInstance().scroll!=0){
      this->currentCutterpillar->viewBack += (float)inputActions::getInstance().scroll/1.5;
      if(this->currentCutterpillar->viewBack > 0.0f) this->currentCutterpillar->viewBack = 0.0f;
      if(this->currentCutterpillar->viewBack < -60.0f) this->currentCutterpillar->viewBack = -60.0f;
   }
   //std::cout << inputActions::getInstance().rightClick << std::endl;
   if(inputActions::getInstance().rightClick){
      if(this->currentCutterpillar->tmpViewBack > 0) this->currentCutterpillar->tmpViewBack = this->currentCutterpillar->viewBack;
      if(this->currentCutterpillar->viewBack < -20) this->currentCutterpillar->viewBack=0.0f;
   }
   else{
       if(this->currentCutterpillar->tmpViewBack <= 0 ){
         this->currentCutterpillar->viewBack = this->currentCutterpillar->tmpViewBack;
         this->currentCutterpillar->tmpViewBack=666.0f;
      }
      //printf("odl: %f\n",this->currentCutterpillar->tmpViewBack);
   }


   this->start = clock();
}
bool Game::checkCollisionAndMove(Object *o,glm::vec3 pos, std::vector<Object*> v){
   return checkCollisionAndMove(o,pos.x,pos.y,pos.z,v);
}
bool Game::checkCollisionAndMove(Object *o,float x, float y, float z ,std::vector<Object*> v){
   bool canX = true;
   bool canY = false;
   bool canZ = true;

   if(x<=5 || x>vertX-5)
      canX = false;
   if(y<=0 || y>maxMapHeight+300)
      canY = false;
   if(z<=5 || z>vertY-5)
      canZ = false;

   //..................TODO kolizja z mapą X
   //..................TODO kolizja z mapą Z

   for(int i=0; i< v.size(); i++)
   {
     //Jesli wieza
     if(dynamic_cast<Tower *>(v[i]))
     {
       //cout << i <<" : Tower" << endl;
       //kolizja z Tower
       if((x >= (int)v[i]->pos.x - (v[i]->size.x/2)) && (x <= (int)v[i]->pos.x + (v[i]->size.x/2))
          && (z >= (int)v[i]->pos.z - (v[i]->size.z/2)) && (z <= (int)v[i]->pos.z + (v[i]->size.z/2)))
       {
         canX = false;
         canZ = false;
       }
     }
     else if(dynamic_cast<Caterpillar *>(v[i]))
     {
       //cout << i << " : Caterpillar" << endl;

       //Kolizja z Caterpillar

       if(i != Game::currCatIndex)//wykluczenie kolizji z samym soba
       {
         if((x >= (int)v[i]->pos.x - 5) && (x <= (int)v[i]->pos.x + 5)
            && (y >= (int)v[i]->pos.y - 35) && (y <= (int)v[i]->pos.y + 35)
            && (z >= (int)v[i]->pos.z - 3) && (z <= (int)v[i]->pos.z + 3))
         {
           canX = false;
           canY = false;
           canZ = false;
         }
       }


     }
   }

   if(((int)o->pos.x>=0) && ((int)o->pos.x <vertX) && ((int)o->pos.z>=0) && ((int)o->pos.z<vertY)){//jesli jest na mapie
     if(y-(o->size.y) > Map::getInstance().mapVert[(int)x][(int)z]) // Tu ta 30 jest troche slaba
         canY=true;
      else{
         //canX=false;
         //canZ=false;
         y=Map::getInstance().mapVert[(int)x][(int)z]+(o->size.y);
      }
   }

   if(canX)
      o->pos.x = x;
   if(canY)
      o->pos.y = y;
   if(canZ)
      o->pos.z = z;

   return canY;
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
         glm::vec3(cos(inputActions::getInstance().movedX/300),0.0f,sin(inputActions::getInstance().movedX/300)),
         glm::vec3(0.0f,1.0f,0.0f),
         glm::vec3(-sin(inputActions::getInstance().movedX/300),0.0f,cos(inputActions::getInstance().movedX/300))
      );
      viewVec=rotM*viewVec;
      this->lookAt=viewVec+this->lookFrom;
   }
   if(inputActions::getInstance().movedY!=0){
      //Tak być nie powinno! (ale jakoś działa :( )
      //Poza tym to tylko do testów więc może zostać :)
      this->lookAt[1]-=inputActions::getInstance().movedY/2;
   }
}

void Game::pressESC() {
    inputActions::getInstance().changeState('p',this->window,this->cursor);
    inputActions::getInstance().cursorFixedCenterPos=false;
}
