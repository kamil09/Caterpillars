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

void inputActions::getMouseCurrentPosition(GLFWwindow* window){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    this->cursorLastX=xpos;
    this->cursorLastY=ypos;
    std::cout << "Cursor X: " << this->cursorLastX << " Cursor Y: " << this->cursorLastY << std::endl;
}


double inputActions::getCursorLastX(){
    return this->cursorLastX;
}

double inputActions::getCursorLastY(){
    return this->cursorLastY;
}

void inputActions::key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
    inputActions().getInstance().currentState->key_callback(window, key, scancode, action, mods);
}
void inputActions::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
    inputActions::getInstance().currentState->cursor_pos_callback(window, xpos, ypos);
}
void inputActions::mouse_button_callback(GLFWwindow* window, int key, int action, int mods){
    inputActions::getInstance().currentState->mouse_button_callback(window, key, action, mods);
}
void inputActions::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    inputActions::getInstance().currentState->scroll_callback(window, xoffset, yoffset);
}



void inputActions::setCallbacks(GLFWwindow* window,GLFWcursor* cursor){
	glfwSetKeyCallback(window, inputActions::key_callback);
	cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);
	glfwSetCursorPosCallback(window, inputActions::getInstance().cursor_pos_callback);
	glfwSetMouseButtonCallback(window, inputActions::getInstance().mouse_button_callback);
	glfwSetScrollCallback(window, inputActions::getInstance().scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
