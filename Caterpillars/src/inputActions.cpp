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
	this->SHIFT_pressed=false;

	this->leftClick=false;
	this->rightClick=false;
	this->lastLeftClick=false;

	this->cursorLastX=0;
	this->cursorLastY=0;
	this->movedX=0;
	this->movedY=0;

	this->lastX=0;
	this->lastY=0;

	this->cursorFixedCenterPos=false;
	this->cursorDisabled=false;
}

void inputActions::clear(){
	this->scroll=0;
	this->movedX=0;
	this->movedY=0;
}

inputActions::~inputActions(){}

inputActions& inputActions::getInstance(){
	static inputActions instance;
	return instance;
}

void inputActions::getMouseCurrentPosition(GLFWwindow* window){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	this->cursorLastX=xpos;
	this->cursorLastY=ypos;
}

double inputActions::getCursorLastX(){
	return this->cursorLastX;
}

double inputActions::getCursorLastY(){
	return this->cursorLastY;
}

void inputActions::key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
	if(action == GLFW_PRESS){
		inputActions::getInstance().keys[key] = true;
	}
	else if(action == GLFW_RELEASE){
		inputActions::getInstance().keys[key] = false;
	}
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

GLFWcursor * inputActions::setCallbacks(GLFWwindow *window, GLFWcursor *cursor){
	glfwSetKeyCallback(window, inputActions::key_callback);
	cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);
	glfwSetCursorPosCallback(window, inputActions::getInstance().cursor_pos_callback);
	glfwSetMouseButtonCallback(window, inputActions::getInstance().mouse_button_callback);
	glfwSetScrollCallback(window, inputActions::getInstance().scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	return cursor;
}

void inputActions::changeCursor(int shape){
	if(this->cursorShape != shape) {
		this->cursorShape = shape;
		GLFWcursor* cursor = glfwCreateStandardCursor(shape);
		glfwSetCursor(this->currentState->window, cursor);
	}
}

State *inputActions::findState(char key, GLFWwindow *window, GLFWcursor *cursor) {
	char upKey = toupper(key);
	std::map<char,State*>::iterator it = this->mapStates.find(upKey);
	if(it != this->mapStates.end() ){
		State *result =it->second;
		return result;
	}
	else{
		std::cout << "Tworzenie" << std::endl;
		return this->createState(upKey,window,cursor);
	}
}

State *inputActions::createState(char key, GLFWwindow *window, GLFWcursor *cursor) {
	State *temp = nullptr;
	State *state;
	switch(key){
		case 'M':
			temp = new MainMenu(window,cursor);
			this->mapStates.insert(std::make_pair('M',temp));
			break;
		case 'G':
			temp = new Game(window,cursor);
			this->mapStates.insert(std::make_pair('G',temp));
			break;
		case 'O':
			state = this->findState('M',window,cursor);
			if(state!= nullptr){
				temp = new OptionMenu(state,window,cursor);
				this->mapStates.insert(std::make_pair('O',temp));
			}
			break;
		case 'S':
			state = this->findState('M',window,cursor);
			if(state!= nullptr){
				temp = new GameMenu(state,window,cursor);
				this->mapStates.insert(std::make_pair('S',temp));
			}
			break;
		case 'L':
			state = this->findState('M',window,cursor);
			if(state!= nullptr){
				temp = new LoadingScreen(state,window,cursor);
				this->mapStates.insert(std::make_pair('L',temp));
			}
			break;
		case 'P':
			state = this->findState('G',window,cursor);
			if(state!= nullptr){
				temp = new PauseMenu(state,window,cursor);
				this->mapStates.insert(std::make_pair('P',temp));
			}
			break;
	}
	return temp;
}


void inputActions::changeState(char key, GLFWwindow *window, GLFWcursor *cursor) {
	State* newState = this->findState(key,window,cursor);
	if(newState!= nullptr) this->currentState = newState;
}
