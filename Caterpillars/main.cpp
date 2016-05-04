#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "src/settings.hpp"
#include "src/2dView.hpp"
#include "src/button.hpp"
#include "src/inputActions.hpp"

using namespace std;
using namespace glm;




//ERROR
static void error_callback(int error, const char* description);
//KLAWIATURA
static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods );
//KURSOR
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
//MYSZ
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//INICJALIZACJA
void initOpenGLProgram(GLFWwindow* window,GLFWcursor* cursor);

//MAIN
int main(void){
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) return 1;
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	GLFWwindow* window;
	if ( Setting::getInstance().getFullWindow() ){
		if (Setting::getInstance().getFullResolution() ) window = glfwCreateWindow(mode->width, mode->height, "Caterpillars",glfwGetPrimaryMonitor(), NULL);
		else window = glfwCreateWindow(Setting::getInstance().getWidth(), Setting::getInstance().getHeight(), "Caterpillars",glfwGetPrimaryMonitor(), NULL);
	}
	else{
		if (Setting::getInstance().getFullResolution() ) window = glfwCreateWindow(mode->width, mode->height, "Caterpillars",NULL, NULL);
		else window = glfwCreateWindow(Setting::getInstance().getWidth(), Setting::getInstance().getHeight(), "Caterpillars",NULL, NULL);
	}

	std::cout << Setting::getInstance().getHeight() << std::endl;
	std::cout << Setting::getInstance().getWidth() << std::endl;

	if(!window) {
		std::cerr << "terminated" << std::endl;
		glfwTerminate();
		return 1;
	}
	GLFWcursor* cursor=0;
	initOpenGLProgram(window,cursor);

	glViewport(0,0,mode->width,mode->height);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);


	Button *nowyButton = new Button(100,0.0f,0.0f,0.5f,0.5f);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	   glClear(GL_COLOR_BUFFER_BIT);
		switch (gameCase) {
			case START:
				mainMenuView();
				break;
			case OPTIONS:
				optionsView();
				break;
			case INFO:
				infoView();
				break;
			case GAME:
				//DRAW 3D scene
				gameView(); //draw 2d
				break;
			case PAUSE:
				//DRAW 3D scene
				pauseView(); //draw 2d
				break;
			case GAME_END:
				gameEndView();
				break;
			case EXIT:
				exitView();
				break;
		}
			nowyButton->rysuj();
		// Draw our first triangle
		        // glUseProgram(shaderProgram);
		        // glBindVertexArray(VAO);
		        // //glDrawArrays(GL_TRIANGLES, 0, 6);
		        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		        // glBindVertexArray(0);

		glfwSwapBuffers(window);
		//Czyścimy niektóre inputy przed kolejną klatką.
		inputActions::getInstance().clear();
		glfwPollEvents();
	}

	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);

	glfwDestroyCursor(cursor);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}


void initOpenGLProgram(GLFWwindow* window,GLFWcursor* cursor){
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint VertexArrayID;							//TODO : PO CO TO? :)
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLenum error_code = glewInit();
	if(error_code != GLEW_OK) {
		std::cerr << "Glew init error: " << glewGetErrorString(error_code) << std::endl;
	}

	glfwSetKeyCallback(window, key_callback);
	cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Informacje o sprzęcie:" << std::endl << vendor << std::endl << renderer << std::endl << version << std::endl << shading << std::endl;

}
static void error_callback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}
static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
//move
	if(key == GLFW_KEY_W && action == GLFW_PRESS) inputActions::getInstance().w_pressed=true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) inputActions::getInstance().w_pressed=false;
	if(key == GLFW_KEY_A && action == GLFW_PRESS) inputActions::getInstance().a_pressed=true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) inputActions::getInstance().a_pressed=true;
	if(key == GLFW_KEY_S && action == GLFW_PRESS) inputActions::getInstance().s_pressed=true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) inputActions::getInstance().s_pressed=true;
	if(key == GLFW_KEY_D && action == GLFW_PRESS) inputActions::getInstance().d_pressed=true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) inputActions::getInstance().d_pressed=true;
//jump (jeżeli połączony z jakimś z powyższych to skaczemy w kierunku)
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) inputActions::getInstance().space_pressed=true;
//show/close inventory
	if(key == GLFW_KEY_I && action == GLFW_PRESS) inputActions::getInstance().i_pressed=true;
//close / pause
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) inputActions::getInstance().escape_pressed=true;
}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	inputActions::getInstance().movedX=xpos-inputActions::getInstance().lastX;
	inputActions::getInstance().movedY=ypos-inputActions::getInstance().lastY;
	inputActions::getInstance().lastX=xpos;
	inputActions::getInstance().lastY=ypos;
}
static void mouse_button_callback(GLFWwindow* window, int key, int action, int mods){
	if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) inputActions::getInstance().leftClick=true;
	if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		inputActions::getInstance().leftClick=false;
		inputActions::getInstance().lastLeftClick=true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		inputActions::getInstance().cursorLastX=xpos;
		inputActions::getInstance().cursorLastY=ypos;
	}
	if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) inputActions::getInstance().rightClick=true;
	if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) inputActions::getInstance().rightClick=false;
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	inputActions::getInstance().escape_pressed+=yoffset;
}
