#include "state.hpp"
#include "../inputActions.hpp"


State::State(GLFWwindow *currenWindow, GLFWcursor *cur){
    this->cursor = cur;
    this->window = currenWindow;
    this->customPollEvents = false;
    inputActions::getInstance().cursorFixedCenterPos=false;
    GLint viewport[4];
	 glGetIntegerv(GL_VIEWPORT, viewport);
	//TODO: Sprawdzić czy dziala dla wielu rozdzielczosci

//	this->windowXsize=1366.0f;
//    this->windowYsize=768.0f;
	this->windowXsize=viewport[2];
    this->windowYsize=viewport[3];
}

void State::key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
   if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		inputActions::getInstance().SHIFT_pressed=true;
	}
	if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		inputActions::getInstance().SHIFT_pressed=false;
	}
   //WSAD
	if(key == GLFW_KEY_W && action == GLFW_PRESS) {
		inputActions::getInstance().w_pressed=true;
//		this->pressW();
	}
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
		inputActions::getInstance().w_pressed=false;
//		this->releaseW();
	}
	if(key == GLFW_KEY_S && action == GLFW_PRESS) {
		inputActions::getInstance().s_pressed=true;
//		this->pressS();
	}
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
		inputActions::getInstance().s_pressed=false;
//		this->releaseS();
	}
	if(key == GLFW_KEY_A && action == GLFW_PRESS) {
		inputActions::getInstance().a_pressed=true;
//		this->pressA();
	}
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
		inputActions::getInstance().a_pressed=false;
//		this->releaseA();
	}
	if(key == GLFW_KEY_D && action == GLFW_PRESS) {
		inputActions::getInstance().d_pressed=true;
//		this->pressD();
	}
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
		inputActions::getInstance().d_pressed=false;
//		this->releaseD();
	}
	//ESC
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		inputActions::getInstance().escape_pressed=true;
		this->pressESC();
	}
	if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		inputActions::getInstance().escape_pressed=false;
//		this->releaseESC();
	}
	//Space
	//jump (jeżeli połączony z jakimś z powyższych to skaczemy w kierunku)
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		inputActions::getInstance().space_pressed=true;
//		this->pressSpace();
	}
	if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		inputActions::getInstance().space_pressed=false;
//		this->releaseSpace();
	}
	//I
	if(key == GLFW_KEY_I && action == GLFW_PRESS) {
		inputActions::getInstance().i_pressed=true;
//		this->pressI();
	}
	if(key == GLFW_KEY_I && action == GLFW_RELEASE) {
		inputActions::getInstance().i_pressed=false;
//		this->releaseI();
	}
}

void State::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
   inputActions::getInstance().movedX-=inputActions::getInstance().lastX-xpos;
	inputActions::getInstance().movedY-=inputActions::getInstance().lastY-ypos;
   if(inputActions::getInstance().cursorFixedCenterPos){
      glfwSetCursorPos(window,windowXsize/2,windowYsize/2);
	   if(!inputActions::getInstance().cursorDisabled){
		   inputActions::getInstance().cursorDisabled = true;
	   }
//      glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
      inputActions::getInstance().lastX=windowXsize/2;
      inputActions::getInstance().lastY=windowYsize/2;
   }
   else{
	   if(inputActions::getInstance().cursorDisabled){
		   inputActions::getInstance().cursorDisabled = false;
		   glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
	   }
	   inputActions::getInstance().lastX=xpos;
      inputActions::getInstance().lastY=ypos;
   }
}

void State::mouse_button_callback(GLFWwindow* window, int key, int action, int mods){
	if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		inputActions::getInstance().leftClick=true;
		this->pressLMB();
	}
	if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		inputActions::getInstance().leftClick=false;
		inputActions::getInstance().lastLeftClick=true;
		this->releaseLMB();
	}
	if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		inputActions::getInstance().rightClick=true;
		this->pressRMB();
	}
	if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		inputActions::getInstance().rightClick=false;
		this->releaseRMB();
	}
}

void State::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	inputActions::getInstance().scroll+=yoffset;
}


void State::keysControl() {
//	bool *keys = inputActions::getInstance().keys;
	if(inputActions::getInstance().keys[GLFW_KEY_LEFT_SHIFT]){
		this->pressShift();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_W]){
		this->pressW();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_S]){
		this->pressS();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_A]){
		this->pressA();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_D]){
		this->pressD();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_ESCAPE]){
//		std::cout << "hej" << std::endl;
		this->pressESC();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_SPACE]){
		this->pressSpace();
	}
	if(inputActions::getInstance().keys[GLFW_KEY_I]){
		this->pressI();
	}
}