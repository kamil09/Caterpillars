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
}

inputActions::~inputActions(){

}

inputActions& inputActions::getInstance(){
	// static Setting *instance = new Setting();
	// return *instance;
	static inputActions instance;
	return instance;
}
