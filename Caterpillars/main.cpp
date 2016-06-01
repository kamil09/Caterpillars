#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "src/settings.hpp"
// #include "src/2dView.hpp"
// #include "src/button.hpp"
#include "src/state/game/map/map.hpp"
#include "src/inputActions.hpp"
#include "src/state/state.hpp"
#include "src/state/game/game.hpp"
#include "src/state/menu/menu.hpp"
#include "src/state/menu/mainMenu/mainMenu.hpp"
#include <unistd.h>
#include "src/errorGL.hpp"
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// #include "src/font.hpp"

using namespace std;
using namespace glm;

//ERROR
static void error_callback(int error, const char* description);
//INICJALIZACJA
void initOpenGLProgram(GLFWwindow* window,GLFWcursor* cursor);
//ZMIANA stanu
// void changeState(gameCaseType statNum,GLFWwindow* window,GLFWcursor* cursor);

//MAIN
int main(void){
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) return 1;
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	// std::cout << "Monitor width: " << mode->width << " monitor height: " << mode->height << std::endl;
	glfwWindowHint(GLFW_SAMPLES, 16); // 4x antialiasing
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

	// glfwSetWindowSize(window, mode->width, mode->height);
	// window = glfwCreateWindow(800, 600, "Caterpillars",NULL, NULL);

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
	// glViewport(0,0,800,600);


	// glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	errorCheck("inicjalizacja");
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(inputActions::getInstance().currentState->customPollEvents == false){
			glfwPollEvents();
		}

		// if(inputActions::getInstance().changeState) changeState(inputActions::getInstance().nextState,window,cursor);
	   inputActions::getInstance().currentState->run();
		errorCheck("Rysowanie");

		glfwSwapBuffers(window);
		//Czyścimy niektóre inputy przed kolejną klatką.
		inputActions::getInstance().clear();
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
	errorCheck("Przed glewInit");
	GLenum error_code = glewInit();
	if(error_code != GLEW_OK) {
		std::cerr << "Glew init error: " << glewGetErrorString(error_code) << std::endl;
	}
	errorCheck("Po glewInit");
	MainMenu *mainMenu = new MainMenu(window,cursor);
	inputActions::getInstance().currentState = mainMenu;
	inputActions::getInstance().setCallbacks(window,cursor);

	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Informacje o sprzęcie:" << std::endl << vendor << std::endl << renderer << std::endl << version << std::endl << shading << std::endl;

	// Font::initFt();
}

static void error_callback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}

//
// void changeState(gameCaseType statNum,GLFWwindow* window,GLFWcursor* cursor){
// 	inputActions::getInstance().changeState = false;
// 	   switch (statNum) {
//         case gameCaseType::MAIN:{
// 		  		MainMenu *mainMenu = new MainMenu(window,cursor);
// 				inputActions::getInstance().currentState = mainMenu;
// 			}
//         break;
//         case gameCaseType::START:{
// 		  		Game *game = new Game(window,cursor);
// 				inputActions::getInstance().currentState = game;
// 			}
//         break;
//         case gameCaseType::OPTIONS:{
//
// 		  }
//         break;
//         case gameCaseType::INFO:{
//
// 		  }
//         break;
//         case gameCaseType::GAME_ST:{
//
// 		  }
//         break;
//         case gameCaseType::PAUSE:{
//
// 		  }
//         break;
//         case gameCaseType::GAME_END:{
//
// 		  }
//         break;
//         case gameCaseType::EXIT:{
// 			  exit(0);
// 		  }
//         break;
// 		  default:;
//     }
// 	 inputActions::getInstance().setCallbacks(window,cursor);
// }
