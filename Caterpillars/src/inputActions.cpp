#include "inputActions.hpp"


inputActions::inputActions(){
   this->w_pressed=false;
   this->a_pressed=false;
   this->s_pressed=false;
   this->d_pressed=false;
   this->space_pressed=false;
   this->i_pressed=false;
   this->escape_pressed=false;
   this->scroll=0;

   this->leftClick=false;
   this->rightClick=false;
   this->lastLeftClick=false;

   this->cursorLastX=0;
   this->cursorLastY=0;
   this->movedX=0;
   this->movedY=0;

   this->lastX=0;
   this->lastY=0;
}

void inputActions::clear(){
   this->scroll=0;
   this->movedX=0;
   this->movedY=0;
}

inputActions::~inputActions(){

}

inputActions& inputActions::getInstance(){
	static inputActions instance;
	return instance;
}
