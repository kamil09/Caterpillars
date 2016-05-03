#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "src/settings.hpp"
#include "src/2dView.hpp"
#include "src/button.hpp"

using namespace std;
using namespace glm;

//ERROR
static void error_callback(int error, const char* description);
//KLAWIATURA
static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods );
//KURSOR
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
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
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
	//if(key == W && action == GLFW_PRESS)
	//if(key == W && action == GLFW_RELEASE)
	//if(key == A && action == GLFW_PRESS)
	//if(key == A && action == GLFW_RELEASE)
	//if(key == S && action == GLFW_PRESS)
	//if(key == S && action == GLFW_RELEASE)
	//if(key == D && action == GLFW_PRESS)
	//if(key == D && action == GLFW_RELEASE)
//jump (jeżeli połączony z jakimś z powyższych to skaczemy w kierunku)
	//if(key == SPACE && action == GLFW_PRESS)
	//if(key == SPACE && action == GLFW_RELEASE)
//show/close inventory
	//if(key == I && action == GLFW_PRESS)
	//if(key == I && action == GLFW_RELEASE)

//close / pause
	//if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

}
